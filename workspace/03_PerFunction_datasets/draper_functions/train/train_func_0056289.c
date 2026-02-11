find_parens(const uschar *ptr, int count, const uschar *name, int lorn,
  BOOL xmode)
{
const uschar *thisname;

for (; *ptr != 0; ptr++)
  {
  int term;


  if (*ptr == '\\')
    {
    if (*(++ptr) == 0) return -1;
    if (*ptr == 'Q') for (;;)
      {
      while (*(++ptr) != 0 && *ptr != '\\');
      if (*ptr == 0) return -1;
      if (*(++ptr) == 'E') break;
      }
    continue;
    }


  if (*ptr == '[')
    {
    while (*(++ptr) != ']')
      {
      if (*ptr == 0) return -1;
      if (*ptr == '\\')
        {
        if (*(++ptr) == 0) return -1;
        if (*ptr == 'Q') for (;;)
          {
          while (*(++ptr) != 0 && *ptr != '\\');
          if (*ptr == 0) return -1;
          if (*(++ptr) == 'E') break;
          }
        continue;
        }
      }
    continue;
    }


  if (xmode && *ptr == '#')
    {
    while (*(++ptr) != 0 && *ptr != '\n');
    if (*ptr == 0) return -1;
    continue;
    }


  if (*ptr != '(') continue;
  if (ptr[1] != '?' && ptr[1] != '*')
    {
    count++;
    if (name == NULL && count == lorn) return count;
    continue;
    }

  ptr += 2;
  if (*ptr == 'P') ptr++;


  if ((*ptr != '<' || ptr[1] == '!' || ptr[1] == '=') &&
       *ptr != '\'')
    continue;

  count++;

  if (name == NULL && count == lorn) return count;
  term = *ptr++;
  if (term == '<') term = '>';
  thisname = ptr;
  while (*ptr != term) ptr++;
  if (name != NULL && lorn == ptr - thisname &&
      strncmp((const char *)name, (const char *)thisname, lorn) == 0)
    return count;
  }

return -1;
}
