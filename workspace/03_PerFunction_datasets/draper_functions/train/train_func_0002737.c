LocaleCompare(const char *p,const char *q)
{
  int
    result;

  if (p == (char *) NULL)
    result=-1;
  else if (q == (char *) NULL)
    result=1;
  else
    {
      register unsigned int
	c,
	d,
	i;

      i=0;
      while (1)
	{
	  c=(unsigned int) ((unsigned char *) p)[i];
	  d=(unsigned int) ((unsigned char *) q)[i];
	  if ((c == 0U) || (AsciiMap[c] != AsciiMap[d]))
	    break;
	  i++;
	}
      result=AsciiMap[c]-AsciiMap[d];
    }
  return result;
}
