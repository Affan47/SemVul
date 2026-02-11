is_integer_syntax (const char *str, int len, int radix)
{
  const char *p = str;
  const char *p_end = str + len;


  if (p == p_end)
    return false;
  if (*p == '+' || *p == '-')
    {
      p++;
      if (p == p_end)
        return false;
    }
  do
    {
      int c = *p++;

      if (c >= '0' && c <= '9')
        c = c - '0';
      else if (c >= 'A' && c <= 'F')
        c = c - 'A' + 10;
      else if (c >= 'a' && c <= 'f')
        c = c - 'a' + 10;
      else
        return false;
      if (c >= radix)
        return false;
    }
  while (p < p_end);
  return true;
}
