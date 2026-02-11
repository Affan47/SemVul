strndup(const char* s, size_t n) {

  size_t l = strlen(s);
  char* r = NULL;

  if (l < n)
    return strdup(s);

  r = (char*) malloc(n + 1);
  if (r == NULL)
    return NULL;

  strncpy(r, s, n);
  r[n] ='\0';
  return r;
}
