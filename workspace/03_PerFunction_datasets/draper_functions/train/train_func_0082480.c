Stream_Gets(char *str, int size, StmInf *pstm)
{
  int c;
  char *p = str;

  for (;;)
    {
      if (p - str >= size)
	break;

      c = Stream_Getc(pstm);

      if (c == EOF)
	break;

      *p++ = c;

      if (c == '\n')
	break;
    }

  if (c == EOF && p == str)
    return NULL;

  *p = '\0';
  return str;
}
