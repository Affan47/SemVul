mg_mmap(FILE *fp, size_t size) {
  void *p = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fileno(fp), 0);
  return p == MAP_FAILED ? NULL : p;
}
