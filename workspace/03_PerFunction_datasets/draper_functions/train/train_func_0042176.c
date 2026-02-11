compat_strdup(const char *s)
{
  size_t size;
  char *p;

  RUNTIME_ASSERT(s);
  size = strlen(s) + 1;
  RUNTIME_ASSERT(size > 0 && size <= INT_MAX);
  p = (char *) malloc(size);
  if (p) {
    memcpy(p, s, size);
  }
  return p;
}
