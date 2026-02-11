strstr(const char *s, const char *find) {
  size_t len;
  const char c = *find++;
  if (c != '\0') {
    len = strlen(find);
    do {
      char sc;
      do {
        if ((sc = *s++) == '\0') return (NULL);
      } while (sc != c);
    } while (strncmp(s, find, len) != 0);
    s--;
  }
  return ((char *)s);
}
