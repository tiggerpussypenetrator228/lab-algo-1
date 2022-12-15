#include <iostream>

#include <random>
#include <chrono>
#include <cstdlib>

void improved_bubble_sort(int* INPUT, short N)
{
  for (int i = 0; i < N - 1; i++)
  {
    for (int j = 0; j < N - i - 1; j++)
    {
      if (INPUT[j] > INPUT[j + 1])
      {
        int temp = INPUT[j];

        INPUT[j] = INPUT[j + 1];
        INPUT[j + 1] = temp;
      }
    }
  }
}

void bubble_sort(int* INPUT, short N)
{
B1:
  short BOUND = N - 1 ;

B2:
  if (BOUND == 0)
  {
    return;
  }

  short t = 0;

  for (short j = 0; j <= BOUND - 1; j++)
  {
  B3:
    int Kj = INPUT[j];
    int Kj1 = INPUT[j + 1];
    if (Kj > Kj1)
    {
      INPUT[j + 1] = Kj;
      INPUT[j] = Kj1;

      t = j;
    }
  }

B4:
  BOUND = t;
  goto B2;
}

void create_input(int** pINPUT, short N)
{
  srand(time(NULL));
  *pINPUT = new int[N];

  for (int i = 0; i < N; i++)
  {
    (*pINPUT)[i] = rand() % (N * 100);
  }
}

void free_input(int* INPUT)
{
  delete[] INPUT;
}

void print_array(int* INPUT, short N)
{
  for (int i = 0; i < N; i++)
  {
    std::cout << INPUT[i] << " ";
  }
}

std::chrono::high_resolution_clock::time_point capture_time()
{
  return std::chrono::high_resolution_clock::now();
}

std::chrono::microseconds get_delay(
  std::chrono::high_resolution_clock::time_point pointA, 
  std::chrono::high_resolution_clock::time_point pointB
)
{
  return std::chrono::duration_cast<std::chrono::microseconds>(pointB - pointA);
}

int main(int argc, char** argv)
{
  short N = 100;

  if (argc >= 2) 
  {
    N = std::atoi(argv[1]);
  }
  else 
  {
    std::cout << "Enter amount of array elements:" << std::endl;
    std::cin >> N;
    std::cout << std::endl;
  }

  int* INPUT;

  std::cout << std::endl << std::endl << "UNSORTED ARRAY FOR (bubble):" << std::endl << std::endl;

  create_input(&INPUT, N);
  print_array(INPUT, N);

  auto bubbleSortStartTime = capture_time();
  bubble_sort(INPUT, N);
  auto bubbleSortEndTime = capture_time();

  std::cout << std::endl << std::endl << "AFTER SORTING (bubble):" << std::endl << std::endl;

  print_array(INPUT, N);
  free_input(INPUT);

  std::cout << std::endl << std::endl << "UNSORTED ARRAY FOR (qsort):" << std::endl << std::endl;

  create_input(&INPUT, N);
  print_array(INPUT, N);

  auto qsortStartTime = capture_time();
  std::qsort(INPUT, N, sizeof(INPUT[0]), [](const void* x, const void* y) -> int {
    const int xi = *static_cast<const int*>(x);
    const int yi = *static_cast<const int*>(y);

    if (xi > yi)
    {
      return 1;
    }
    else if (xi < yi)
    {
      return -1;
    }

    return 0;
  });
  auto qsortEndTime = capture_time();

  std::cout << std::endl << std::endl << "AFTER SORTING (qsort):" << std::endl << std::endl;

  print_array(INPUT, N);
  free_input(INPUT);

  std::cout << std::endl << std::endl << "UNSORTED ARRAY FOR (improved_bubble):" << std::endl << std::endl;

  create_input(&INPUT, N);
  print_array(INPUT, N);

  auto improvedBubbleSortStartTime = capture_time();
  improved_bubble_sort(INPUT, N);
  auto improvedBubbleSortEndTime = capture_time();

  std::cout << std::endl << std::endl << "AFTER SORTING (improved_bubble):" << std::endl << std::endl;

  print_array(INPUT, N);
  free_input(INPUT);

  std::cout << std::endl << std::endl << "Sorting took: " << std::endl;
  std::cout << get_delay(bubbleSortStartTime, bubbleSortEndTime).count() << " microseconds for Bubble Sort." << std::endl;
  std::cout << get_delay(qsortStartTime, qsortEndTime).count() << " microseconds for qsort." << std::endl;
  std::cout << get_delay(improvedBubbleSortStartTime, improvedBubbleSortEndTime).count() << " microseconds for Improved Bubble Sort." << std::endl;

  return 0;
}