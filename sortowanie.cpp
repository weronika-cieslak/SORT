
#include <iostream>
#define FACTOR 2
#define MIN_SIZE 2
#include <time.h>
template<typename T>
struct node
{
	T field;
	node *previous;
	node *next;
	node(T field)
	{
		this->field = field;
		this->previous = NULL;
		this->next = NULL;
	}

	void set_field(T field)
	{
		this->field = field;
	}
};
template<typename T>
class List {
public:
	node<T> *head=NULL;
	node<T> *tail=NULL;
	int size_of_list = 0;
	int get_size()
	{
		return size_of_list;
	}
	void add_at_tail(T data)
	{
		node<T> *node_to_add = new node<T>(data);

		if (head == NULL)
		{
			head = node_to_add;
			head->previous = NULL;
			head->next = NULL;
			tail = head;
		}
		else if (head== tail)
		{
			tail = node_to_add;
			tail->next = NULL;
			tail->previous = head;
			head->next = tail;
		}
		else
		{
			tail->next = node_to_add;
			node_to_add->previous = tail;
			tail = node_to_add;
		}
		size_of_list++;
	}
	void add_element_front(T data)
	{
		node<T> *node_to_add = new node<T>(data);

		if (head == NULL) {

			head = node_to_add;

		}
		else {
			node_to_add->previous = NULL;
			node_to_add->next = head;
			head->previous = node_to_add;
			head = node_to_add;
		}
		size_of_list++;
	}
	void delete_last_element()
	{
		if (tail != NULL)
		{
			node<T> *temp = NULL;
			temp = tail;
			tail = tail->previous;
			tail->next = NULL;
			delete temp;
		}
		else if (head != NULL)
		{
			delete head;
		}

		size_of_list--;
	}
	node<T> *find_node_by_index(int index)
	{
		int current_index = 0;
		node<T> *current = head;
		while (current_index != index && current != NULL)
		{
			current = current->next;
			current_index++;
		}
		return current;
	}
	T get(int index)
	{
		node<T> *current = find_node_by_index(index);
		return current->field;
	}
	void replace_data(T data, int index)
	{
		int current_index = 0;
		node<T> *current = find_node_by_index(index);
		if (current != NULL)
		{
			std::cout << "Podmieniamy ten element: " << (current->field) << "\n";
			current->set_field(data);
		}
	}
	void clear()
	{
		node<T>* temp;
		while (head != NULL)
		{
			temp = head;
			head = head->next;
			temp->previous = NULL;
			delete(temp);
		}

		size_of_list = 0;
	}
	node<T> *search_element(T data)
	{
		node<T> *current = head;
		while (current->field != data)
		{
			current = current->next;
			if (current == NULL)
			{
				return current;
			}
		}
		if (current->field == data)
		{
			return current;
		}
	}
	void search_and_delete(T data)
	{
		node<T> *current = search_element(data);

		if (current != NULL)
		{
			node<T> *temp = NULL;
			temp = current;
			current = current->previous;
			current->next = current->next->next;
			delete temp;
		}
	}
	void sort()
	{
		node<T> *it_1 = NULL;
		node<T> *it_2 = NULL;
		T data;
		T data1;
		for (it_1 = head; it_1 != tail->next; it_1 = it_1->next)
		{
			for (it_2 = head; it_2 != tail->next; it_2 = it_2->next)
			{
				if (it_1->field < it_2->field)
				{
					data = it_1->field;
					data1 = it_2->field;
					it_1->set_field(data1);
					it_2->set_field(data);

				}
			}
		}
	}
	void add_element_with_sequence(T data)
	{
		this->add_at_tail(data);
		this->sort();
	}
	void display_list()
	{
		std::cout << "Liczba przechowywanych elementow: " << size_of_list << "\n";
		for (int i = 0; i < size_of_list; i++)
		{
			std::cout << this->get(i) << "\n";
		}
	}
};
template<typename T>
class Dynamic_Array
{
public:
	size_t size;
	size_t capacity;
	T*array;
	Dynamic_Array()
	{

		size = 0;
		capacity = MIN_SIZE;
		array = new T[capacity];
	}

	~Dynamic_Array()
	{
		for (int i = 0; i < size; i++)
		{
			this->array[i] = this->array[i + 1];
			delete array[i];
		}
		delete array;

		size = 0;
		capacity = MIN_SIZE;
	}
	int get_size()
	{
		return this->size;
	}
	
	void set_size(int n)
	{
		this->size = n;
	}
	T get(int index)
	{
		return array[index];
	}
	void replace_data(int index, T data)
	{
		this->array[index] = data;
	}
	void clear()
	{
		size = 0;
		delete[] array;
		capacity = MIN_SIZE;
		array = new T[capacity];
	}
	void display_array()
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << "Index: " << i << " " << this->get(i) << "\n";
		}
	}
	void delete_first_element()
	{
		array[0] = array[size - 1];
		array[size - 1] = T();
		size--;
	}
	bool compare(int index1, int index2)
	{
		if (this->array[index1] < this->array[index2])
		{
			std::cout << "true\n";
			return true;
		}
		else {
			std::cout << "false\n";
			return false;
		}
	}
};
template<typename T>
class Binary_Heap
{
	Dynamic_Array<T> *bh_array;

public:
	Binary_Heap(T *array1,int n,bool sort)
	{
		bh_array = new Dynamic_Array<T>();
		bh_array->array = array1;
		bh_array->set_size(n);
		if(sort==true)
		sort_1(bh_array->array, n);
		else sort_2(bh_array->array, n);
	}
	int get_parent_index(int index)
	{
		if (index == 1)
		{
			return 0;
		}
		int parent_index = (index - 1) / 2;
		return parent_index;
	}
	int get_left_child_index(int index)
	{
		int left_child_index = (2 * index) + 1;
		return left_child_index;
	}
	int get_right_child_index(int index)
	{
		int right_child_index = (2 * index) + 2;
		return right_child_index;
	}
	void bottom_up(T*arr, int n, int index)
	{
		T temp;
		int largest = index; 
		int left_child=get_left_child_index(index); 
		int right_child=get_right_child_index(index); 
		if (left_child < n && arr[left_child] > arr[largest])
			largest = left_child;
		if (right_child < n && arr[right_child] > arr[largest])
			largest = right_child;

		if (largest != index) 
		{
			temp = bh_array->get(index);
			bh_array->replace_data(index, bh_array->get(largest));
			bh_array->replace_data(largest, temp);
			bottom_up(arr, n, largest);
		}
	}
	void top_down(T*arr, int n, int index)
	{
		T temp;
		int parent_index = get_parent_index(index);
		int largest = parent_index;

		if (arr[parent_index] < arr[index])
		{
			largest = index;
			
		}
		if (largest != parent_index)
		{
			temp = bh_array->get(index);
			bh_array->replace_data(index, bh_array->get(parent_index));
			bh_array->replace_data(parent_index, temp);
			top_down(arr, n, parent_index);
		}
	}
	void sort_1(T* arr, int n)
	{
		T temp;
		
		for (int i = n / 2 - 1; i >= 0; i--)
		{
			bottom_up(arr, n, i);
		}
		for (int i = n - 1; i > 0; i--) 
		{
			temp = bh_array->get(0);
			bh_array->replace_data(0, bh_array->get(i));
			bh_array->replace_data(i, temp);
            bottom_up(arr, i, 0);
		}
	}
	void sort_2(T *arr, int n)
	{
		T temp;
		for (int i = n / 2 - 1; i < n; i++)
		{
			top_down(arr, n, i);

		}
		for (int j = n - 1; j > 0; j--)
		{
			temp = bh_array->get(0);
			bh_array->replace_data(0, bh_array->get(j));
			bh_array->replace_data(j, temp);
			for (int k = j - 1; k > 0; k--) 
			{
				top_down(arr, j,k);
			}
		}
	}
	void display()
	{
		bh_array->display_array();
	}
	void clear()
	{
		bh_array->clear();
		bh_array = new Dynamic_Array<T>();

	}
};
struct stored_data
{
	int int_data;
	char char_data;

	void generate_data()
	{
		const char letters[] = "abcdefghijklmnopqrstuvwxyz";
		this->int_data = rand() % 1000;
		this->char_data = letters[rand() % (sizeof(letters) - 1)];

	}
	friend std::ostream& operator<<(std::ostream& os, const stored_data& sd)
	{
		os << "Dane przechowywane: " << sd.int_data << " " << sd.char_data << "\n";
		return os;
	}
	friend bool operator==(const stored_data &st, const stored_data&sd)
	{
		if (st.int_data == sd.int_data &&st.char_data == sd.char_data)
			return true;
		else
			return false;
	}
	friend bool operator !=(const stored_data& st, const stored_data&sd)
	{
		if (st.int_data == sd.int_data &&st.char_data == sd.char_data)
			return false;
		else
			return true;
	}
	friend bool operator <(const stored_data&  so1, const stored_data& so2)
	{
		int diff = so1.int_data - so2.int_data;
		if (diff < 0)
			return true;
		else
			return false;
	}
	friend bool operator >(const stored_data&  so1, const stored_data& so2)
	{
		int diff = so1.int_data - so2.int_data;
		if (diff > 0)
			return true;
		else
			return false;
	}
	friend int operator /(const stored_data& sd1, int d)
	{
		int x = sd1.int_data / d;
		return x;
	}
};
int *bucket_sort(int *array,int n,int m)
{
	List<int>*array_list;
	array_list = new List<int>[n];
	int width= m/n;
	
	for (int i = 0; i < n; i++)
	{
		int index = array[i] / width;
		array_list[index].add_element_with_sequence(array[i]); 
	}
	int index = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < array_list[i].get_size(); j++)
		{
			array[index] = array_list[i].get(j);
			index++;
		}
	}
	array_list->clear();
	delete[]array_list;
	return array;
}
template <typename T>
T *bucket_sort(T *array, int n, int m)
{
	List<T>*array_list;
	array_list = new List<T>[n];
	int width = m / n;

	for (int i = 0; i < n; i++)
	{
		int index = array[i] / width;
		array_list[index].add_element_with_sequence(array[i]);
	}
	int index = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < array_list[i].get_size(); j++)
		{
			array[index] = array_list[i].get(j);
			index++;
		}
	}
	array_list->clear();
	delete[]array_list;
	return array;
}
void counting_sort(int *a, int n, int m)
{
	int *counts = new int[m];
	for (int i = 0; i < m; i++)
	{
		counts[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		counts[a[i]]++;
	}
	int k = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < counts[i]; j++)
		{
			a[k++] = i;
		}
	}
	delete[] counts;
}

int main()
{
	srand(time(NULL));

	int * array1 = new int[20];
	for (int i = 0; i < 20; i++)
	{
		int rand_val = rand() % 1000; 
		array1[i] = rand_val;
	}
	int * array2 = new int[20];
	int * array3 = new int[20];
	memcpy(array2, array1, 20 * sizeof(int)); 
	memcpy(array3, array1, 20 * sizeof(int)); 
	for (int i = 0; i < 20; i++)
	{

		std::cout << array1[i] << "\n";
	}
	std::cout << "\n\n";
	counting_sort(array1,20,1000);
	for (int i = 0; i < 20; i++)
	{
		
		std::cout << array1[i] << "\n";
	}
	std::cout << "\n\n";

	Binary_Heap <int>* bh = new Binary_Heap<int>(array2,20,true);
	for (int i = 0; i < 20; i++)
	{

		std::cout << array2[i] << "\n";
	}
	std::cout << "\n\n";

	bucket_sort(array3, 20, 1000); 
	for (int i = 0; i < 20; i++)
	{

		std::cout << array3[i] << "\n";
	}
	

	delete[]array1,array2,array3;
	stored_data *st=new stored_data[5];
	for (int i = 0; i < 5; i++)
	{
		st[i].generate_data();
	}
	st = bucket_sort(st, 5, 1000);
	for (int i = 0; i < 5; i++)
	{
		std::cout << st[i] << "\n";

	}
	delete[]st;

	
}



// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
