#include <iostream>
#include <chrono>
using namespace std;

/// <summary>
/// Вывод массива на консоль
/// </summary>
/// <param name="array">Массив</param>
/// <param name="N">Размер массива</param>
template<typename T> void Print(T array[], int N) {
	for (int i = 0; i < N; i++) {
		cout << array[i] << " ";
	}
	cout << "\n" << endl;
}

/// <summary>
/// Функция исправления кучи
/// </summary>
/// <param name="index">Индекс, с которого нужно исправить кучу</param>
/// <param name="heap">Массив, который представляет кучу</param>
/// <param name="N">Длина массива</param>
/// <returns>Количество перестановок, выполненных в ходе исправление кучи</returns>
template<typename T> int FixHeap(int index, T heap[], int N) {
	int count = 0;
	while (true) {
		int left = 2 * index + 1, right = 2 * index + 2, largest = index;
		if (left < N && heap[left] > heap[index]) {
			largest = left;
		}
		else{
			largest = index;
		}
		if (right < N && heap[right] > heap[largest]) {
			largest = right;
		}
		if (largest == index) {
			return count;
		}
		swap(heap[index], heap[largest]);
		index = largest;
		count++;
	}
	return count;
}

/// <summary>
/// Построение кучи
/// </summary>
/// <param name="heap">Массив, который нужно преобразовать</param>
/// <param name="N">Длина массива</param>
template<typename T> void BuildHeap(T array[], int N) {
	for (int i = N / 2 - 1; i >= 0; i--) {
		FixHeap(i, array, N);
	}
}

/// <summary>
/// Функция сортировки кучи
/// </summary>
/// <param name="heap">Массив, который нужно отсортировать</param>
/// <param name="N">Длина массива</param>
/// <returns>Количество перестановок, выполненных в ходе сортировки</returns>
template<typename T> int HeapSort(T heap[], int N) {
	int count = 0;
	BuildHeap(heap, N);
	for (int i = N - 1; i > 0; i--) {
		swap(heap[0], heap[i]);
		count += FixHeap(0, heap, i);
	}
	return count;
}

int main()
{
	setlocale(LC_ALL, "RU");
	{
		int N = 10;
		cout << "\t" << "Исходная куча:" << endl;
		int* heap = new int[N] {18, 10, 12, 8, 9, 10, 4, 5, 3, 7};
		//double* heap = new double[N] {18.3, 10.0, 14.0, 8.9, 8.1, 12.0, 4.0, 5.0, 3.0, 7.0};
		Print(heap, N);

		cout << "\t" << "Плохая куча:" << endl;
		heap = new int[N] {18, 9, 10, 8, 10, 12, 4, 5, 3, 7};
		//heap = new double[N] {18.3, 7.0, 14.0, 8.9, 10.0, 12.0, 4.0, 5.0, 3.0, 8.1};
		Print(heap, N);

		cout << "\t" << "Исправленная куча за " << FixHeap(1, heap, N) + FixHeap(2, heap, N) << " итерации:" << endl;
		Print(heap, N);

		cout << "\t" << "Отсортированная куча за " << HeapSort(heap, N) << " итерации:" << endl;
		Print(heap, N);

		delete[]heap;
	}



#pragma region Изучение сложности алгоритма
	{
		int N = 16;
		int* heap;
		while (N <= 12288) {
			heap = new int[N];
			for (int i = 0; i < N; heap[i] = (rand() % 10), i++);
			//for (int i = 0; i < N; heap[i] = i, i++);
			//for (int i = N - 1; i >= 0; heap[i] = i, i--);
			//for (int i = 0; i < N; heap[i] = 1, i++);

			auto start = chrono::steady_clock::now();
			int k = HeapSort(heap, N);
			auto stop = chrono::steady_clock::now();
			auto dt = chrono::duration_cast<chrono::microseconds>(stop - start).count();

			cout << "Размер: " << N << ", кол-во перестановок: " << k << ", время: " << dt << endl;
			N *= 2;
		}
		delete[]heap;
	}
#pragma endregion



}