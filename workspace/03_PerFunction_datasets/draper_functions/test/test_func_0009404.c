strcmpnull(const char *s1, const char *s2)
{
  int r;

  dtrace("%p, %p", s1, s2);

  if (s1 == NULL && s2 == NULL) {
    dreturn("%i", 0);
    return 0;
  }

  if (s1 == NULL) {
    dreturn("%i", -1);
    return -1;
  }

  if (s2 == NULL) {
    dreturn("%i", 1);
    return 1;
  }

  r = strcmp(s1, s2);

  dreturn("%i", r);
  return r;
}
