#ifndef MAP_HPP
#define MAP_HPP

/*
	Name 		: Suhas Mastud
	Class		: cs540-AOOP
	Description 	: Implement a container class template named Map similar to the std::map class from the C++ Standard Library. 

*/

#include <iostream>
#include <stdexcept>
#include <assert.h>

namespace cs540{

template <typename Key_T, typename Mapped_T>
class MapNode
{
	public:
		std::pair<const Key_T, Mapped_T> data;
		MapNode<Key_T, Mapped_T> *next, *prev, *parent, *left, *right;
		int height;
		
	/*	MapNode()
			: next(NULL), prev(NULL), parent(NULL), left(NULL), right(NULL), height(0)
		{}*/

		MapNode(Key_T key, Mapped_T value)
			: data(std::make_pair(key, value)), next(NULL), prev(NULL), parent(NULL), left(NULL), right(NULL), height(0)
		{ }

};

template <typename Key_T, typename Mapped_T>
class Map 
{
	public:
		typedef std::pair<const Key_T, Mapped_T> ValueType;
		class Iterator
		{
			public:
				MapNode<Key_T, Mapped_T> * current;
				Iterator() : current(NULL){};
				Iterator(const Iterator &);
				~Iterator() { }
				Iterator& operator=(const Iterator &);
				Iterator& operator++();
				Iterator operator++(int);
				Iterator &operator--();
				Iterator operator--(int);
				ValueType& operator*() const;
				ValueType *operator->() const;
		};
		class ConstIterator
		{
			public:
				MapNode<Key_T, Mapped_T> * current;
				ConstIterator() : current(NULL){};
				ConstIterator(const ConstIterator &);
				ConstIterator(const Iterator &);
				~ConstIterator() { };
				ConstIterator& operator=(const ConstIterator &);
				ConstIterator &operator++();
				ConstIterator operator++(int);
				ConstIterator &operator--();
				ConstIterator operator--(int);
				const ValueType &operator*() const;
				const ValueType *operator->() const;
		};

		class ReverseIterator
		{
			public:
				MapNode<Key_T, Mapped_T> * current;
				ReverseIterator() : current(NULL) {}
				ReverseIterator(const ReverseIterator &);
				~ReverseIterator() { }
				ReverseIterator& operator=(const ReverseIterator &);
				ReverseIterator &operator++();
				ReverseIterator operator++(int);
				ReverseIterator &operator--();
				ReverseIterator operator--(int);
				ValueType &operator*() const;
				ValueType *operator->() const;
		};

		Map();
		~Map();
		Map(const Map &);
		Map& operator=(const Map &);
		Map(std::initializer_list<std::pair<const Key_T, Mapped_T>>);

		std::pair<Iterator, bool> insert(const ValueType &);
		template<typename IT_T>
		void insert(IT_T range_beg, IT_T range_end);
		void incrementHeight(MapNode<Key_T, Mapped_T> *current);
		int getHeight(MapNode<Key_T, Mapped_T> *paramNode);
		int getBalance(MapNode<Key_T, Mapped_T> *paramNode);
		void clean(MapNode<Key_T, Mapped_T> * current);
		void clear();
		MapNode<Key_T, Mapped_T> * rotateLeft(MapNode<Key_T, Mapped_T> *root, MapNode<Key_T, Mapped_T> *current);
		MapNode<Key_T, Mapped_T> * rotateRight(MapNode<Key_T, Mapped_T> *root, MapNode<Key_T, Mapped_T> *current);
		size_t size() const;
		bool empty() const;
		Mapped_T &at(const Key_T &);
		const Mapped_T &at(const Key_T &) const;
		Iterator find(const Key_T &);
		ConstIterator find(const Key_T &) const;
		Iterator begin();
		Iterator end();
		ConstIterator begin() const;
		ConstIterator end() const;
		ReverseIterator rbegin();
		ReverseIterator rend();
		void erase(const Key_T &);
		void erase(Iterator pos);
		Mapped_T& operator[](const Key_T &);
		friend bool operator==(const Iterator& it1, const Iterator& it2){
			return (it1.current == it2.current);
		}
		friend bool operator==(const ConstIterator &it1, const ConstIterator &it2){
			return (it1.current == it2.current);
		}
		friend bool operator==(const Iterator &it1, const ConstIterator &it2){
			return (it1.current == it2.current);
		}
		friend bool operator==(const ConstIterator &it1, const Iterator &it2){
			return (it1.current == it2.current);
		}
		friend bool operator!=(const Iterator &it1, const Iterator &it2){
			return !(it1 == it2);
		}
		friend bool operator!=(const ConstIterator &it1, const ConstIterator &it2){
			return !(it1 == it2);
		}
		friend bool operator!=(const Iterator &it1, const ConstIterator &it2){
			return !(it1 == it2);
		}
		friend bool operator!=(const ConstIterator &it1, const Iterator &it2){
			return !(it1 == it2);
		}
		friend bool operator==(const ReverseIterator &it1, const ReverseIterator &it2){
			return (it1.current == it2.current);
		}
		friend bool operator!=(const ReverseIterator &it1, const ReverseIterator &it2){
			return !(it1 == it2);
		}
		friend bool operator==(const Map &map1, const Map &map2)
		{
			if(map1.size() != map2.size())
			{
				return false;
			}
			
			auto it1 = map1.begin();
			auto it2 = map2.begin();
			for( ; it1 != map1.end(); ++it1, ++it2)
			{
				if(it1.current->data.first == it2.current->data.first && it1.current->data.second == it2.current->data.second)
				{
					continue;
				}
				else
				{
					return false;
				}
			}
			return true;
		}
		friend bool operator!=(const Map &map1, const Map &map2)
		{
			return !(map1 == map2);
		}

	private:
		MapNode<Key_T, Mapped_T> *head, *tail, *root;
		size_t map_size;

};

/*------------------------------------map default constructor---------------------------------------*/
template <typename Key_T, typename Mapped_T>
Map <Key_T, Mapped_T> :: Map()
	: head(NULL), tail(NULL), root(NULL), map_size(0)
{
//		printf("in default constructor\n");
		MapNode<Key_T, Mapped_T> *tempLastDummyNode = (MapNode<Key_T, Mapped_T> *)malloc(sizeof(MapNode<Key_T, Mapped_T>));
		MapNode<Key_T, Mapped_T> *tempFirstDummyNode = (MapNode<Key_T, Mapped_T> *)malloc(sizeof(MapNode<Key_T, Mapped_T>));
		
		tempLastDummyNode->left = NULL;
		tempLastDummyNode->right = NULL;
		tempLastDummyNode->parent = NULL;
		tempLastDummyNode->next = NULL;
		tempLastDummyNode->prev = NULL;

		tempFirstDummyNode->left = NULL;
		tempFirstDummyNode->right = NULL;
		tempFirstDummyNode->parent = NULL;
		tempFirstDummyNode->next = NULL;
		tempFirstDummyNode->prev = NULL;
		this->head = tempFirstDummyNode;
		this->tail = tempLastDummyNode;	
		this->head->next = this->tail;
		this->tail->prev = this->head;

}

/*------------------------------------map copy constructor---------------------------------------*/
template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Map(const Map& newMap)
	: head(NULL), tail(NULL), root(NULL), map_size(newMap.map_size)
{
	this->head = newMap.head;
	this->tail = newMap.tail;
	this->root = newMap.root;
	this->map_size = newMap.map_size;
}

/*------------------------------------map initializer_list---------------------------------------*/
template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Map(std::initializer_list<std::pair<const Key_T, Mapped_T>> list)
{
		MapNode<Key_T, Mapped_T> *tempLastDummyNode = (MapNode<Key_T, Mapped_T> *)malloc(sizeof(MapNode<Key_T, Mapped_T>));
		MapNode<Key_T, Mapped_T> *tempFirstDummyNode = (MapNode<Key_T, Mapped_T> *)malloc(sizeof(MapNode<Key_T, Mapped_T>));

		tempLastDummyNode->left = NULL;
		tempLastDummyNode->right = NULL;
		tempLastDummyNode->parent = NULL;
		tempLastDummyNode->next = NULL;
		tempLastDummyNode->prev = NULL;

		tempFirstDummyNode->left = NULL;
		tempFirstDummyNode->right = NULL;
		tempFirstDummyNode->parent = NULL;
		tempFirstDummyNode->next = NULL;
		tempFirstDummyNode->prev = NULL;
		this->head = tempFirstDummyNode;
		this->tail = tempLastDummyNode;	
		this->head->next = this->tail;
		this->tail->prev = this->head;		
		this->root = NULL;
		this->map_size = 0;
	for(auto element : list)
	{
		this->insert(element);
	}
}


/*------------------------------------map destructor--------------------------------------*/
template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::~Map()
{
	clean(this->head->next);
	free(this->head);
	free(this->tail);
	this->head = NULL;
	this->tail = NULL;
}
/*------------------------------------helper function to clear data from map---------------------------------------*/
template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::clean(MapNode<Key_T, Mapped_T> * current)
{
//	printf("in clean \n");
	if(current->next == NULL){		

		return;
	}
	current=current->next;
	delete current->prev;
	current->prev = NULL;
	clean(current);
}

/*------------------------------------clear---------------------------------------*/
template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::clear()
{
//	printf("in clear---- \n");
	MapNode<Key_T, Mapped_T> * current = this->head->next;
	clean(current);
}

template <typename Key_T, typename Mapped_T>
Mapped_T& Map<Key_T, Mapped_T>::operator[](const Key_T &key){

	Map<Key_T, Mapped_T>::Iterator it = find(key);
	
	if(it == end()){
		it = (insert({ key, Mapped_T { } })).first;
	}
	return it.current->data.second;
}


template <typename Key_T, typename Mapped_T>
std::pair< typename Map<Key_T, Mapped_T>::Iterator, bool> Map<Key_T, Mapped_T>::insert(const ValueType& dataToInsert)
{
	Iterator it;
	if(this->map_size==0) // map empty
	{
		MapNode<Key_T, Mapped_T> *newMapNode = new MapNode<Key_T, Mapped_T>(dataToInsert.first, dataToInsert.second);

		newMapNode->height = newMapNode->height+1;
			
		this->root = newMapNode;
		this->head->next = newMapNode;
		newMapNode->prev = this->head;
		
		this->tail->prev = newMapNode;
		newMapNode->next = this->tail;
		this->map_size++;
		
		it.current = newMapNode; // Iterator pointing to new created node
	}
	else // map not empty
	{
		MapNode<Key_T, Mapped_T> *current = this->root;
		bool nodeInsertedFlag=false;
		while(true)
		{		
			
			if(current->data.first == dataToInsert.first) // key present in a map, return pair
			{
				it.current= current;
				return std::make_pair(it, false);
			}
				
			else // key is not present in a map
			{
				if(current->data.first < dataToInsert.first) // current node's key is smaller than new node key
				{
					if(current->right == NULL) // no right child present, then insert at left
					{
						MapNode<Key_T, Mapped_T> *newMapNode = new MapNode<Key_T, Mapped_T>(dataToInsert.first, dataToInsert.second);

						current->right = newMapNode;
						newMapNode->parent = current;
						current->next = newMapNode;
						newMapNode->prev = current;
						newMapNode->height = newMapNode->height + 1;
						this->map_size++;
						
						
						it.current = newMapNode; // Iterator pointing to new created node

						MapNode<Key_T, Mapped_T> * tempRootIncrement = current;
						while(tempRootIncrement!=NULL)
						{
							tempRootIncrement->height = getHeight(tempRootIncrement);
							tempRootIncrement = tempRootIncrement->parent;
						}


						nodeInsertedFlag=true;	
						if(current->parent!=NULL) //changing next and prev 
						{
							if(dataToInsert.first < current->parent->data.first )
							{	
								current->parent->prev = newMapNode;
								newMapNode->next = current->parent;
							}
							else
							{
								
								if(current->parent == this->root)
								{
									newMapNode->next = this->tail;
									this->tail->prev = newMapNode;
								}
								else
								{

									MapNode<Key_T, Mapped_T> *tempCurrent = current->parent;
									while(tempCurrent->parent!=NULL && tempCurrent->data.first < dataToInsert.first)
									{
										tempCurrent = tempCurrent->parent;
									}
									if(tempCurrent == this->root)
									{
										if(this->root->data.first < dataToInsert.first)
										{
											while(tempCurrent->right!=NULL)
											{
												tempCurrent = tempCurrent->right;
											}
											tempCurrent->next = this->tail;
											this->tail->prev = tempCurrent;
										}
										else
										{
											tempCurrent->prev = newMapNode;
											newMapNode->next = tempCurrent;
										}									
									}
									else
									{	
										tempCurrent->prev = newMapNode;
										newMapNode->next = tempCurrent;
									}
								}
							}
						}
						else
						{
							newMapNode->next = this->tail;
							this->tail->prev = newMapNode;
						}
						break;		
					}
					else
					{
						current= current->right;
					}
				}
				else // current node's key is greater than new node key
				{
					if(current->left == NULL) // no left child present, then insert at left
					{
						MapNode<Key_T, Mapped_T> *newMapNode = new MapNode<Key_T, Mapped_T>(dataToInsert.first, dataToInsert.second);

						current->left = newMapNode;
						newMapNode->parent = current;
						current->prev = newMapNode;
						newMapNode->next = current;
						
						newMapNode->height = newMapNode->height + 1;
						this->map_size++;
						it.current = newMapNode; // Iterator pointing to new created node		
						
						MapNode<Key_T, Mapped_T> * tempRootIncrement = current;
						while(tempRootIncrement!=NULL)
						{
							tempRootIncrement->height = getHeight(tempRootIncrement);
							tempRootIncrement = tempRootIncrement->parent;
						}						

						if(current->parent!=NULL) //changing next and prev 
						{
							if(current->parent->data.first < dataToInsert.first)
							{	
								current->parent->next = newMapNode;
								newMapNode->prev = current->parent;
							}
							else
							{
								if(current->parent == this->root)
								{
									newMapNode->prev = this->head;
									this->head->next = newMapNode;
								}
								else
								{
									MapNode<Key_T, Mapped_T> *tempCurrent = current->parent;
									while(tempCurrent->parent!= NULL && dataToInsert.first < tempCurrent->data.first)
									{
										tempCurrent = tempCurrent->parent;
									}
									if(tempCurrent == this->root)
									{
										if(dataToInsert.first < this->root->data.first)
										{
											while(tempCurrent->left!=NULL)
											{
												tempCurrent = tempCurrent->left;
											}
											tempCurrent->prev = this->head;
											this->head->next = tempCurrent;
										}
										else
										{
											tempCurrent->next = newMapNode;
											newMapNode->prev = tempCurrent;
										}
									}
									else
									{
										tempCurrent->next = newMapNode;
										newMapNode->prev = tempCurrent;
									}
								}							
							}
						}
						else
						{
							newMapNode->prev = this->head;
							this->head->next = newMapNode;
						}
						nodeInsertedFlag=true;	
						break;
					}
					else
					{
						current= current->left;
					}
				}
			}
			 
			
		}//end while true loop
		if(nodeInsertedFlag)
		{
			int balfac = getBalance(current->parent);
			if(balfac == 2)
			{
				if(getBalance(current) == -1)
				{
					this->root=rotateRight(root,current);
					this->root=rotateLeft(root,current->parent);
					MapNode<Key_T, Mapped_T> * tempRootDecrement = current;
					while(tempRootDecrement!=NULL)
					{
						tempRootDecrement->height = getHeight(tempRootDecrement);
						tempRootDecrement = tempRootDecrement->parent;
					}
				}
				else if(getBalance(current) == 1)
				{
					this->root=rotateLeft(root,current->parent);
					MapNode<Key_T, Mapped_T> * tempRootDecrement = current;
					while(tempRootDecrement!=NULL)
					{
						tempRootDecrement->height = getHeight(tempRootDecrement);
						tempRootDecrement = tempRootDecrement->parent;
					}
				}
			}
			else if(balfac == -2)
			{
				if(getBalance(current) == 1)
				{
					this->root=rotateLeft(root,current);
					this->root=rotateRight(root,current->parent);
					MapNode<Key_T, Mapped_T> * tempRootDecrement = current;
					while(tempRootDecrement!=NULL)
					{
						tempRootDecrement->height = getHeight(tempRootDecrement);
						tempRootDecrement = tempRootDecrement->parent;
					}
				}
				else if(getBalance(current) == -1)
				{
					this->root=rotateRight(root,current->parent);
					MapNode<Key_T, Mapped_T> * tempRootDecrement = current;
					while(tempRootDecrement!=NULL)
					{
						tempRootDecrement->height = getHeight(tempRootDecrement);
						tempRootDecrement = tempRootDecrement->parent;
					}
				}
			}
			else
			{
//				printf("no need to rotate\n");
			}
		}
		else
		{
//			printf("no need to balanse as no node inserted\n");
		}
	}
	return std::make_pair(it, true);
}

template<typename K, typename V>
template<typename IT_T>
void Map<K, V>::insert(IT_T range_beg, IT_T range_end) {
	while (range_beg != range_end) 
	{
		insert(*range_beg);
		++range_beg;
	}
}


template <typename Key_T, typename Mapped_T>
MapNode<Key_T, Mapped_T> * Map<Key_T, Mapped_T>::rotateRight(MapNode<Key_T, Mapped_T> *root, MapNode<Key_T, Mapped_T> *current)
{
	MapNode<Key_T, Mapped_T> *temp = current->left;
	if(root == current)
	{
		root = temp;
	}
	else
	{
		if(current->parent->right == current)
		{
			current->parent->right = temp;
		}
		else
		{
			current->parent->left = temp;
		}
	}
	current->left = temp->right;
	if(current->left != NULL)
	{
		current->left->parent = current;
	}
	temp->parent = current->parent;
	current->parent = temp;
	temp->right = current;
	current->height = getHeight(current);
	temp->height = getHeight(temp);
	return root;
}


template <typename Key_T, typename Mapped_T>
MapNode<Key_T, Mapped_T> * Map<Key_T, Mapped_T>::rotateLeft(MapNode<Key_T, Mapped_T> *root, MapNode<Key_T, Mapped_T> *current)		
{
	MapNode<Key_T, Mapped_T> *temp = current->right;
	if(root == current)
	{
		root = temp;
	}
	else
	{
		if(current->parent->right == current)
		{
			current->parent->right = temp;
		}
		else
		{
			current->parent->left = temp;
		}
	}
	current->right = temp->left;
	if(current->right != NULL)
	{
		current->right->parent = current;
	}
	temp->parent = current->parent;
	current->parent = temp;
	temp->left = current;
	current->height = getHeight(current);
	temp->height = getHeight(temp);
	return root;
}



template <typename Key_T, typename Mapped_T>
int Map<Key_T, Mapped_T>::getBalance(MapNode<Key_T, Mapped_T> *paramNode)
{
	int leftheight,rightheight;
	if(paramNode != NULL)
	{
		leftheight = getHeight(paramNode->left);
		rightheight = getHeight(paramNode->right);
		return (rightheight - leftheight);
	}
	return 0;
}

template <typename Key_T, typename Mapped_T>
int Map<Key_T, Mapped_T>::getHeight(MapNode<Key_T, Mapped_T> *paramNode)
{
	int leftChildHeight=0,rightChildHeight=0;
	if(paramNode==NULL)
	{
		return 0;
	}
	if(paramNode->left!=NULL)
	{
		leftChildHeight=paramNode->left->height;
	}
	if(paramNode->right!=NULL)
	{
		rightChildHeight=paramNode->right->height;
	}
	if(leftChildHeight>=rightChildHeight)
	{
		return (1+leftChildHeight);
	}
	else
	{
		return (1+rightChildHeight);
	}

}


template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::incrementHeight(MapNode<Key_T, Mapped_T> *current)
{
	while(current!=NULL)
	{
		current->height=current->height+1;
		current=current->parent;
	}
}

template <typename Key_T, typename Mapped_T>
Mapped_T& Map<Key_T, Mapped_T>::at(const Key_T &key)
{
	MapNode<Key_T, Mapped_T> * temp = this->root;
	int flag=0;	
	if(temp!=NULL)
	{
	
			while(temp!=NULL)
			{
				if(temp->data.first == key)
				{
					flag=1;
					break;
				}
				else if(temp->data.first < key)
				{
					temp = temp->right;
				}
				else
				{
					temp = temp->left;
				}
			}
	}
	if(flag==0)
	{
		throw std::out_of_range("Key is not present in a map\n");
	}
	return temp->data.second;
}

template <typename Key_T, typename Mapped_T>
const Mapped_T& Map<Key_T, Mapped_T>::at(const Key_T &key) const
{
	MapNode<Key_T, Mapped_T> * temp = this->root;
	int flag=0;	
	if(temp!=NULL)
	{
		if(temp->data.first == key)
		{
			flag=1;
		}
		else
		{
			while(true)
			{
				if(temp->data.first < key)
				{
					temp = temp->right;
				}
				else
				{
					temp = temp->left;
				}
			}
		}
	}
	if(flag==0)
	{
		throw std::out_of_range("Key is not present in a map\n");
	}
	return temp->data.second;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::find(const Key_T &key)
{
	Map<Key_T, Mapped_T>::Iterator it;
	MapNode<Key_T, Mapped_T> * temp = this->head->next;

	int flag=0;
	while(temp->next!=NULL)
	{
		if(temp->data.first == key)
		{
			flag=1;	
			break;
		}
		else
		{
			temp = temp->next;
		}
	}
	if(flag == 0)
	{
		it = this->end();
	}
	else
	{
		it.current = temp;
	}
	return it;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::find(const Key_T &key) const
{
	Map<Key_T, Mapped_T>::ConstIterator it;
	MapNode<Key_T, Mapped_T> * temp = this->head->next;

	int flag=0;
	while(temp->next!=NULL)
	{
		if(temp->data.first == key)
		{
			flag=1;	
			break;
		}
		else
		{
			temp = temp->next;
		}
	}
	if(flag == 0)
	{
		it = end();
	}
	else
	{
		it.current = temp;
	}
	return it;
}


template <typename Key_T, typename Mapped_T>
size_t Map<Key_T, Mapped_T>::size() const
{
	return this->map_size;
}

template <typename Key_T, typename Mapped_T>
bool Map<Key_T, Mapped_T>::empty() const
{
	if(this->map_size > 0)
	{
		return true;
	}
	return false;
}

template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Iterator::Iterator(const Map<Key_T, Mapped_T>::Iterator& newIterator)
{
	this->current = newIterator.current;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator& Map<Key_T, Mapped_T>::Iterator::operator=(const Map<Key_T, Mapped_T>::Iterator& newIterator)
{
	if(this == &newIterator)
	{
		return *this;
	}
	this->current = newIterator.current;
	return *this;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator& Map<Key_T, Mapped_T>::Iterator::operator++()
{
	current = current->next;
	return *this;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::Iterator::operator++(int)
{
	Map<Key_T, Mapped_T>::Iterator it(*this);
	++(*this);
	return it;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator& Map<Key_T, Mapped_T>::Iterator::operator--()
{
	current = current->prev;
	return *this;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::Iterator::operator--(int)
{
	Map<Key_T, Mapped_T>::Iterator it(*this);
	--(*this);
	return it;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType& Map<Key_T, Mapped_T>::Iterator::operator*() const
{
	return (this->current->data);
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType* Map<Key_T, Mapped_T>::Iterator::operator->() const
{
	return &(this->current->data);
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::begin()
{
	Map<Key_T, Mapped_T>::Iterator it;
	MapNode<Key_T, Mapped_T> * temp = this->head->next;
	
	if(this->head != NULL)
	{
		it.current = temp;
	}
	return it;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::begin() const
{
	Map<Key_T, Mapped_T>::ConstIterator it;
	MapNode<Key_T, Mapped_T> * temp = this->head->next;
	
	if(this->head != NULL)
	{
		it.current = temp;
	}
	return it;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::end() const{
	Map<Key_T, Mapped_T>::ConstIterator it;
	MapNode<Key_T, Mapped_T> * temp = this->tail;
	
	if(this->tail != NULL)
	{
		it.current = temp;
	}
	return it;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::end()
{
	Map<Key_T, Mapped_T>::Iterator it;
	MapNode<Key_T, Mapped_T> * temp = this->tail;
	
	if(this->tail != NULL)
	{
		it.current = temp;
	}
	return it;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::rbegin()
{
	Map<Key_T, Mapped_T>::ReverseIterator it;
	MapNode<Key_T, Mapped_T> * temp = this->tail->prev;
	
	if(this->tail != NULL)
	{
		it.current = temp;
	}
	it.current = temp;
	return it;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::rend()
{
	Map<Key_T, Mapped_T>::ReverseIterator it;
	MapNode<Key_T, Mapped_T> * temp = this->head;
	
	if(this->head != NULL)
	{
		it.current = temp;
	}
	it.current = temp;
	return it;
}


template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ReverseIterator::ReverseIterator(const Map<Key_T, Mapped_T>::ReverseIterator& newReverseIterator)
{
	this->current = newReverseIterator.current;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator& Map<Key_T, Mapped_T>::ReverseIterator::operator=(const Map<Key_T, Mapped_T>::ReverseIterator& newReverseIterator)
{
	if(this == &newReverseIterator)
	{
		return *this;
	}
	this->current = newReverseIterator.current;
	return *this;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator& Map<Key_T, Mapped_T>::ReverseIterator::operator++()
{
	this->current = this->current->prev;
	return *this;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::ReverseIterator::operator++(int)
{
	Map<Key_T, Mapped_T>::ReverseIterator it(*this);
	++(*this);
	return it;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator& Map<Key_T, Mapped_T>::ReverseIterator::operator--()
{
	this->current = this->current->next;
	return *this;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::ReverseIterator::operator--(int)
{
	Map<Key_T, Mapped_T>::ReverseIterator it(*this);
	--(*this);
	return it;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType& Map<Key_T, Mapped_T>::ReverseIterator::operator*() const
{
	return (this->current->data);
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType* Map<Key_T, Mapped_T>::ReverseIterator::operator->() const
{
	return &(this->current->data);
}

template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ConstIterator::ConstIterator(const Map<Key_T, Mapped_T>::ConstIterator& newConstIterator)
{
	this->current = newConstIterator.current;
}


template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ConstIterator::ConstIterator(const Map<Key_T, Mapped_T>::Iterator& newConstIterator)
{
	this->current = newConstIterator.current;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator&  Map<Key_T, Mapped_T>::ConstIterator::operator=(const Map<Key_T, Mapped_T>::ConstIterator& newConstIterator)
{
	if(this == &newConstIterator)
	{
		return *this;
	}
	this->current = newConstIterator.current;
	return *this;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator&  Map<Key_T, Mapped_T>::ConstIterator::operator++()
{
	this->current = this->current->next;
	return *this;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::ConstIterator::operator++(int)
{
	Map<Key_T, Mapped_T>::ConstIterator it(*this);
	++(*this);
	return it;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator&  Map<Key_T, Mapped_T>::ConstIterator::operator--()
{
	this->current = this->current->prev;
	return *this;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::ConstIterator::operator--(int)
{
	Map<Key_T, Mapped_T>::ConstIterator it(*this);
	--(*this);
	return it;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType const &  Map<Key_T, Mapped_T>::ConstIterator::operator*() const
{
	return this->current->data;
}


template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType const * Map<Key_T, Mapped_T>::ConstIterator::operator->() const
{
	return &(this->current->data);
}

template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::erase(Map<Key_T, Mapped_T>::Iterator position)
{
	erase(position.current->data.first);
}

template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::erase(const Key_T &key)
{
	MapNode<Key_T, Mapped_T> * tempRoot = this->root;
	MapNode<Key_T, Mapped_T> * current = this->root;
	if(this->map_size == 0)
	{
		throw std::out_of_range("Key does not exist in a map!!!\n");
	}
	else
	{
		if(this->root->data.first == key && map_size == 1) // only one node present
		{
			delete this->root;

			this->root=NULL;			
			this->head->next=this->tail;
			this->tail->prev=this->head;
			this->map_size = 0;	
		}
		else
		{
			bool nodeDeletedFlag=false;
			while(tempRoot!=NULL)
			{
				if(key < tempRoot->data.first )
				{
					tempRoot=tempRoot->left;
				}
				else if(tempRoot->data.first < key)
				{
					tempRoot=tempRoot->right;
				}
				else
				{
					if(tempRoot->left == NULL && tempRoot->right == NULL) // leaf node without left and right child
					{
						tempRoot->prev->next = tempRoot->next;
						tempRoot->next->prev = tempRoot->prev;

						if(tempRoot == tempRoot->parent->left)
						{
							tempRoot->parent->left = NULL;
						}
						else if(tempRoot == tempRoot->parent->right)
						{
							tempRoot->parent->right = NULL;
						}
						current = tempRoot->parent;
						MapNode<Key_T, Mapped_T> * tempRootDecrement = tempRoot->parent;
						while(tempRootDecrement!=NULL)
						{
							tempRootDecrement->height = getHeight(tempRootDecrement);
							tempRootDecrement = tempRootDecrement->parent;
						}
					
						tempRoot->parent = NULL;
						tempRoot->prev = NULL;
						tempRoot->next = NULL;

						delete tempRoot;
						tempRoot = NULL; 
						this->map_size = this->map_size - 1;
						nodeDeletedFlag=true;
						break;
					}
					else if(tempRoot->left == NULL && tempRoot->right != NULL && this->root == tempRoot) // node has right child only and this is root
					{
						tempRoot->prev->next = tempRoot->next;
						tempRoot->next->prev = tempRoot->prev;
					
						this->root = tempRoot->right;
						tempRoot->right->parent=NULL;					
						tempRoot->right = NULL;
						tempRoot->prev = NULL;
						tempRoot->next = NULL;	
						delete tempRoot;
						tempRoot = NULL; 
						this->map_size = this->map_size - 1;
						this->root->height = getHeight(this->root);

						break;
					}
					else if(tempRoot->right == NULL && tempRoot->left != NULL && this->root == tempRoot) // node has left child only and this is root
					{
						tempRoot->prev->next = tempRoot->next;
						tempRoot->next->prev = tempRoot->prev;
						this->root = tempRoot->left;					
						
						tempRoot->left->parent=NULL;
						tempRoot->left = NULL;
						tempRoot->prev = NULL;
						tempRoot->next = NULL;	

						delete tempRoot;
						tempRoot = NULL;
						this->map_size = this->map_size - 1;
						this->root->height = getHeight(this->root);

						break;
					}
					else if(tempRoot->left == NULL && tempRoot->right != NULL && this->root != tempRoot) // node has right child only and this is NOT a root
					{
						tempRoot->prev->next = tempRoot->next;
						tempRoot->next->prev = tempRoot->prev;
					
						current = tempRoot->parent;	
	
						if(tempRoot->right->data.first < tempRoot->parent->data.first)
						{
							tempRoot->right->parent = tempRoot->parent;
							tempRoot->parent->left = tempRoot->right;
							tempRoot->right = NULL;
						}
						else if(tempRoot->parent->data.first < tempRoot->right->data.first)
						{
							tempRoot->right->parent = tempRoot->parent;
							tempRoot->parent->right = tempRoot->right;
							tempRoot->right = NULL;
						}		
						MapNode<Key_T, Mapped_T> * tempRootDecrement = tempRoot->parent;
						while(tempRootDecrement!=NULL)
						{
							tempRootDecrement->height = getHeight(tempRootDecrement);
							tempRootDecrement = tempRootDecrement->parent;
						}
					

						delete tempRoot;
						tempRoot = NULL; 
						this->map_size = this->map_size - 1;
						nodeDeletedFlag=true;

						break;
					}
					else if(tempRoot->right == NULL && tempRoot->left != NULL && this->root != tempRoot) // node has left child only and this is NOT a root
					{
						tempRoot->prev->next = tempRoot->next;
						tempRoot->next->prev = tempRoot->prev;

						current = tempRoot->parent;

						if(tempRoot->parent->data.first < tempRoot->left->data.first)
						{
							tempRoot->left->parent = tempRoot->parent;
							tempRoot->parent->right = tempRoot->left;
							tempRoot->left = NULL;
						}
						else if(tempRoot->left->data.first < tempRoot->parent->data.first)
						{
							tempRoot->right->parent = tempRoot->parent;
							tempRoot->parent->left = tempRoot->left;
							tempRoot->left = NULL;
						}
						MapNode<Key_T, Mapped_T> * tempRootDecrement = tempRoot->parent;
						while(tempRootDecrement!=NULL)
						{
							tempRootDecrement->height = getHeight(tempRootDecrement);
							tempRootDecrement = tempRootDecrement->parent;
						}
					
						delete tempRoot;
						tempRoot = NULL;
						this->map_size = this->map_size - 1;
						nodeDeletedFlag=true;
						break;
					}
					else if(tempRoot->right != NULL && tempRoot->left != NULL && this->root == tempRoot) // has left and right child and this is root
					{
						tempRoot->prev->next = tempRoot->next;
						tempRoot->next->prev = tempRoot->prev;
					
						tempRoot->right->left = tempRoot->left;
						tempRoot->left->parent = tempRoot->right;

						this->root = tempRoot->right;
						tempRoot->right->parent=NULL;
						tempRoot->right=NULL;
						tempRoot->next=NULL;
						tempRoot->prev=NULL;
						delete tempRoot;
						tempRoot = NULL;
						this->map_size = this->map_size - 1;
						this->root->height = getHeight(this->root);
						break;
					}
					else if(tempRoot->right != NULL && tempRoot->left != NULL && this->root != tempRoot) // has left and right child and this is NOT a root
					{
						MapNode<Key_T, Mapped_T> * tempRootDecrement = tempRoot->next->parent;
						tempRoot->prev->next = tempRoot->next;
						tempRoot->next->prev = tempRoot->prev;
					
						tempRoot->next->parent->left = NULL;					
						tempRoot->next->parent = tempRoot->parent;
						tempRoot->next->left = tempRoot->left;
						tempRoot->next->right = tempRoot->right;

						current = tempRoot->parent;

						while(tempRootDecrement!=NULL)
						{
							tempRootDecrement->height = getHeight(tempRootDecrement);
							tempRootDecrement = tempRootDecrement->parent;
						}
						delete tempRoot;
						tempRoot = NULL;
						this->map_size = this->map_size - 1;
						nodeDeletedFlag=true;
						break;
					}
				}
			}//end while
			if(nodeDeletedFlag)
			{
				int balfac = getBalance(current->parent);
				if(balfac == 2)
				{
					if(getBalance(current) == -1)
					{
						this->root=rotateRight(this->root,current);
						this->root=rotateLeft(this->root,current->parent);
						MapNode<Key_T, Mapped_T> * tempRootDecrement = current;
						while(tempRootDecrement!=NULL)
						{
							tempRootDecrement->height = getHeight(tempRootDecrement);
							tempRootDecrement = tempRootDecrement->parent;
						}
					}
					else if(getBalance(current) == 1)
					{
						this->root=rotateLeft(this->root,current->parent);
						MapNode<Key_T, Mapped_T> * tempRootDecrement = current;
						while(tempRootDecrement!=NULL)
						{
							tempRootDecrement->height = getHeight(tempRootDecrement);
							tempRootDecrement = tempRootDecrement->parent;
						}
					}
				}
				else if(balfac == -2)
				{
					if(getBalance(current) == 1)
					{
						this->root=rotateLeft(this->root,current);
						this->root=rotateRight(this->root,current->parent);
						MapNode<Key_T, Mapped_T> * tempRootDecrement = current;
						while(tempRootDecrement!=NULL)
						{
							tempRootDecrement->height = getHeight(tempRootDecrement);
							tempRootDecrement = tempRootDecrement->parent;
						}
					}
					else if(getBalance(current) == -1)
					{
						this->root=rotateRight(this->root,current->parent);
						MapNode<Key_T, Mapped_T> * tempRootDecrement = current;
						while(tempRootDecrement!=NULL)
						{
							tempRootDecrement->height = getHeight(tempRootDecrement);
							tempRootDecrement = tempRootDecrement->parent;
						}
					}
				}
				else
				{
//					printf("no need to rotate\n");
				}

			}
			else
			{
//				printf("no need to balance the tree\n");
			}
		}	
	}
}

template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>& Map<Key_T, Mapped_T>::operator=(const Map<Key_T, Mapped_T> &newMap)
{
	if(this == &newMap)
	{
		return *this;
	}

	Map<Key_T, Mapped_T> *tempMap = new Map<Key_T, Mapped_T>();
	tempMap->head = newMap.head;
	tempMap->tail = newMap.tail;
	tempMap->root = newMap.root;
	tempMap->map_size = newMap.map_size;
	return *tempMap;
}


} // end namespace

#endif
