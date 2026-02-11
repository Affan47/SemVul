quicksort(void* base, size_t nmemb, size_t size, int(*compare)(const void*, const void*)) {
  if (base == NULL || compare == NULL)
    return;
  quicksort_rec(base, 0, nmemb - 1, size, compare);
}
