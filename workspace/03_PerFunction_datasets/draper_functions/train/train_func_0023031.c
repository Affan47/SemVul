memcasecmp (const void *vs1, const void *vs2, size_t n)
{
  size_t i;
  char const *s1 = vs1;
  char const *s2 = vs2;
  for (i = 0; i < n; i++)
    {
      unsigned char u1 = s1[i];
      unsigned char u2 = s2[i];
      int U1 = toupper (u1);
      int U2 = toupper (u2);
      int diff = (UCHAR_MAX <= INT_MAX ? U1 - U2
                  : U1 < U2 ? -1 : U2 < U1);
      if (diff)
        return diff;
    }
  return 0;
}
