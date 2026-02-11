strcpyn(char *dst, const char *src, size_t n)
{
  unsigned int ui;
  char *a;
  const char *b;

  a = dst;
  b = src;
  for (ui = 0; ui < n; ui++) {
	if ((*a++ = *b++) == '\0')
	  return(dst);
  }
  *a = '\0';
  return(dst);
}
