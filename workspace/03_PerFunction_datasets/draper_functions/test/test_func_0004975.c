compat_memmem(const void *data, size_t size,
  const void *pattern, size_t pattern_size)
{
  const char *p, *end;

  p = data;
  if (pattern_size > 0) {
    char pat0;
    size_t n;

    end = &p[size];
    pat0 = *(const char *) pattern;

    for (;;) {
      n = end - p;
      p = n < pattern_size ? NULL : memchr(p, pat0, n);
      if (!p || 0 == memcmp(p, pattern, pattern_size)) {
        break;
      }
      p++;
    }
  }
  return (void *) p;
}
