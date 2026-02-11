trim_leading_zeros (char const *s)
{
  char const *p = s;
  while (*s == '0')
    ++s;


  if (!*s && s != p)
    --s;
  return s;
}
