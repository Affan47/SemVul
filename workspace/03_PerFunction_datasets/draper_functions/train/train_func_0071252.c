str_ibegin(const char *s1, const char *s2)
{
char u1, u2;

while (*s1 && *s2)
  {
  u1 = toupper(*s1++);
  u2 = toupper(*s2++);
  if (u1 < u2)
    return -1;
  else if (u1 > u2)
    return  1;
  }
if (*s2)
  return -1;
return 0;
}
