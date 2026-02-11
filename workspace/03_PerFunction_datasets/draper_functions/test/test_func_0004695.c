find_braced_pos (char *str, int words, int chars, int ignore_blanks)
{
  int i;
  int bracelevel;
  char *p = str;
  char c;

  for (i = 0; i < words; i++)
    {
      bracelevel = 1;
      while ((c = *p++) != '{' && c != '\n' && c)
         ;
      if (c != '{')
        return p - 1;
      while (bracelevel)
        {
          c = *p++;
          if (c == '{')
            bracelevel++;
          if (c == '}')
            bracelevel--;
          if (c == 0 || c == '\n')
            return p - 1;
        }
    }

  while ((c = *p++) != '{' && c != '\n' && c)
     ;

  if (c != '{')
    return p - 1;

  if (ignore_blanks)
    while ((c = *p) == ' ' || c == '\t')
      p++;

  for (i = 0; i < chars; i++)
    {
      if (!*p || *p == '\n')
        break;
      p++;
    }
  return p;
}
