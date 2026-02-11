StringChop(char *s)
{
  int   i;

  i = strlen(s) - 1;
  while (i >= 0 && isspace((int) s[i])) i--;
  s[i+1] = '\0';
}
