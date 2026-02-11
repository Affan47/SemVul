parserat(char *s, int *n, int *d) {
  *n = atoi(s);

  while (*s != '\0' && *s != '/') s++;

  if (*s == '\0') {
    *d = 1;
    return 1;
  }

  s++;
  *d = atoi(s);

  return 1;
}
