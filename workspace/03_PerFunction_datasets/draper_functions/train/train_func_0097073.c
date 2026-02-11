dumphb(char *tbl, int beg)
{
  int i, j, k;
  char *p = &tbl[beg - CHAR_MIN];
  unsigned char c;
  for (i = 0; i <= SCHAR_MAX; i += ROWSIZE)
  {
    k = i + ROWSIZE - 1;
    if (k > SCHAR_MAX)
      k = SCHAR_MAX;

    c = (unsigned char)(beg + i);
    printf("/*");
    if ((c > 0) && (c < SCHAR_MAX) && (isprint(c)) && (c != '\\')
	&& (c != '\''))
      printf(" '%c'", c);
    else
      printf(" x%02x", ((int)c));

    c = (unsigned char)(beg + k);
    printf("-");
    if ((c > 0) && (c < SCHAR_MAX) && (isprint(c)) && (c != '\\')
	&& (c != '\''))
      printf("'%c'", c);
    else
      printf("x%02x", ((int)c));
    printf(" */");

    for (j = i; j <= k; j++)
    {
      c = p[j];
      if ((c > 0) && (c < SCHAR_MAX) && (isprint(c)) && (c != '\\')
	  && (c != '\''))
	printf("    '%c'", c);
      else
	printf(" '\\x%02x'", ((int)c));
      if (j < SCHAR_MAX)
	printf(",");
    }
    printf("\n");
  }
}
