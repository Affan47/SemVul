strtrim(char *str, char *trim_chars, int limit)
{
  int n;
  char *p;

  p = str + strlen(str) - 1;
  n = 0;
#ifdef NOTDEF
  while ((!limit || n < limit) && p >= str
		 && strchr(trim_chars, (int) *p) != NULL)
	p--, n++;
#else
  while ((!limit || n < limit) && p >= str
		 && strtr_char((int) *p, trim_chars, 0))
	p--, n++;
#endif

  *(p + 1) = '\0';

  return(str);
}
