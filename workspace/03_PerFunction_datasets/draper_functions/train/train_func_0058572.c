find_braced_end (char *str)
{
  int bracelevel;
  char *p = str;
  char c;

  bracelevel = 1;
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
  return p - 1;
}
