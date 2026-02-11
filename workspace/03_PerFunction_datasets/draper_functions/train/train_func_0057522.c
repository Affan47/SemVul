toUpper (char *str)
{
  if (str == NULL) return;
  int i;
  for (i = 0; i < (int) strlen (str); i ++)
    if (str [i] >= 'a' && str [i] <= 'z')
      str [i] -= 32;
}
