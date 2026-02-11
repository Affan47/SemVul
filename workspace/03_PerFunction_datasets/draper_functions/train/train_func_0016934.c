mpn_diff_highest (mp_srcptr p1, mp_srcptr p2, mp_size_t size)
{
  mp_size_t  i;

  for (i = size-1; i >= 0; i--)
    if (p1[i] != p2[i])
      return i;


  return -1;
}
