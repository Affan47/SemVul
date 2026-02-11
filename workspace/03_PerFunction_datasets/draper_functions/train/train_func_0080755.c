sort_utils_insertionsort (void *const a,
                          const size_t count,
                          const size_t element_size,
                          const sort_utils_compare_function cmp)
{
  char *a_ptr = (char *) a;
  for (int i = 1; i < count; i++) {
    int j = i;
    for (;;) {
      if (j == 0 || cmp(a_ptr + (j - 1) * element_size, a_ptr + j * element_size)) break;
      swap(a_ptr + j * element_size, a_ptr + (j - 1) * element_size, element_size);
      j--;
    }
  }
}
