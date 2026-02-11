sprint_ul_rev (char *s, unsigned long value)
{
  int i = 0;
  do
    {
      s[i] = "0123456789"[value % 10];
      value /= 10;
      i++;


    }
  while (value != 0);
  return i;
}
