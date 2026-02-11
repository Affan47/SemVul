n_occurrences (int c, const char *s)
{
  int n = 0;

  if (s == 0 || *s == '\0')
    return -1;

  while (*s)
    n += (*s++ == c);

  return n;
}
