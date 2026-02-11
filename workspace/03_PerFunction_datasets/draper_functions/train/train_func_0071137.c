string_ncount(const char *src, size_t srclen,
                  const char *charlist, size_t listlen) {
  int i = 0, j = 0;
  int count = 0;

  for (i = 0; i < srclen; i++) {
    for (j = 0; j < listlen; j++) {
      if (src[i] == charlist[j]) {
        count++;
        break;
      }
    }
  }
  return count;
}
