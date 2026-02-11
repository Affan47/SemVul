quicksort_rec(void* base, int begin, int end, size_t size, int(*compare)(const void*, const void*)) {
  int pivot, pivotIndex;
  if (begin < end) {
    pivotIndex = (begin + end) / 2;
    pivot = partition(base, begin, end, size, pivotIndex, compare);
    quicksort_rec(base, begin, pivot - 1, size, compare);
    quicksort_rec(base, pivot + 1, end, size, compare);
  }
}
