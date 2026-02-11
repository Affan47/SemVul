cookie_nextfield(char *a) {
  char *b = a;

  a = strchr(a, '\n');
  if (a == NULL)
    a = b + strlen(b);
  else
    a++;
  while(*a == '\n')
    a++;
  return a;
}
