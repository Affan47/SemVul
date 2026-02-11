bits_ulong(char *s,
	       long unsigned int *np)
{
  int i;
  unsigned long n;

  n = 0;
  for(i = 0 ; s[i] == '0' || s[i] == '1'; i++)
    n = n * 2 + s[i] - '0';
  *np = n;
  return(s[i] == '\0');
}
