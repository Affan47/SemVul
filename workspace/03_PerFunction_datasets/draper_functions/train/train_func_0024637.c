verify(int64_t *dst, const int size) {
  int i;

  for (i = 1; i < size; i++) {
    if (dst[i - 1] > dst[i]) {
      printf("Verify failed! at %d\n", i);

      for (i = i - 2; i < SIZE; i++) {
        printf(" %lld", (long long int)dst[i]);
      }

      printf("\n");
      break;
    }
  }
}
