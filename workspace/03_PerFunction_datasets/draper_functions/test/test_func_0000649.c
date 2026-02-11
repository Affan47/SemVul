SkipThisToken (str, length)
     char *str;
     int length;
{
  if (*str == '-') str++;
  return (str + length);
}
