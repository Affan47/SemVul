lmc_ht_strdup(void *base, const char *s, size_t l) {
  size_t va_s = lmc_valloc(base, l +  sizeof(size_t) + 1);
  if (!va_s) { return 0; }
  char *p = base + va_s;
  *(size_t *) p = l;
  p += sizeof(size_t);
  memcpy(p, s, l + 1);
  return va_s;
}
