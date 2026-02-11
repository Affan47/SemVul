matchCi(const Char *s, size_t n, const char *key)
{
  for (; *key; key++, s++, n--) {
    if (!n)
      return 0;
    if (*s != tolower(*key) && *s != toupper(*key))
      return 0;
  }
  return n == 0;
}
