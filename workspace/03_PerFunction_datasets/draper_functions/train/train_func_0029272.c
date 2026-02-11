ReplaceChars(char* str, const char *toreplace, char replacement)
{
  if (str)
    {
    char *ptr = str;
    while (*ptr)
      {
      const char *ptr2 = toreplace;
      while (*ptr2)
        {
        if (*ptr == *ptr2)
          {
          *ptr = replacement;
          }
        ++ptr2;
        }
      ++ptr;
      }
    }
  return str;
}
