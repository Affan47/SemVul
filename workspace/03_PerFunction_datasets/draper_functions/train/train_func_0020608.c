quote_special_chars(char *s)
{
  char *ptr, *result;
  size_t len;

  if (s == NULL)
    return NULL;

  len = strlen(s) + 1;
  ptr = s;
  while (*ptr != '\0')
  {
    if (
        (*ptr == '\n')
        ||
        (*ptr == '\t')
        ||
        (*ptr == '\\')
       )
      len++;
    ptr++;
  }

  result = (char*)fizmo_malloc(len);
  ptr = result;

  while (*s != '\0')
  {
    if (*s == '\n')
    {
      *ptr = '\\';
      ptr++;
      *ptr = 'n';
    }
    else if (*s == '\t')
    {
      *ptr = '\\';
      ptr++;
      *ptr = 't';
    }
    else if (*s == '\\')
    {
      *ptr = '\\';
      ptr++;
      *ptr = '\\';
    }
    else
    {
      *ptr = *s;
    }
    s++;
    ptr++;
  }
  *ptr = '\0';

  return result;
}
