purgespace(p)
char* p;


{
  int blank;
  char *s;

  blank = 1;
  s = p;
  while (*s != '\0') {
    if (*s != ' ') blank = 0;
    s = s + 1;
  };
  if (blank) {
    *p = '\0';
  };
  return(blank);
}
