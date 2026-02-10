compat_protect_strdup(const char *s)
{
  size_t size;

  size = strlen(s) + 1;
  RUNTIME_ASSERT(size > 0 && size <= INT_MAX);
  return compat_protect_memdup(s, size);
}
