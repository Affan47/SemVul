cval (s, i)
     char *s;
     int i;
{
  size_t tmp;
  wchar_t wc;
  int l;
  mbstate_t mps;

  if (MB_CUR_MAX == 1)
    return ((wchar_t)s[i]);
  l = strlen (s);
  if (i >= (l - 1))
    return ((wchar_t)s[i]);
  memset (&mps, 0, sizeof (mbstate_t));
  tmp = mbrtowc (&wc, s + i, l - i, &mps);
  if (MB_INVALIDCH (tmp) || MB_NULLWCH (tmp))
    return ((wchar_t)s[i]);
  return wc;
}
