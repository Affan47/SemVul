substring(char *str, int start, int len)
{
  int   i;
  char  *ret;
  char  *res;
  char  *ptr;
  char  *end;


  if ((len < 1) || (start < 0) || (start > (int)strlen (str)))
    return NULL;

  if (start+len > (int)strlen(str))
    len = strlen(str) - start;

  ret = xmalloc(len+1);
  res = ret;
  ptr = str;
  end = str;

  for (i = 0; i < start; i++, ptr++) ;
  for (i = 0; i < start+len; i++, end++) ;
  while (ptr < end)
    *res++ = *ptr++;

  *res = 0;
  return ret;
}
