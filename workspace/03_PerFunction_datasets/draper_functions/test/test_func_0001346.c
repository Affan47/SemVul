find_tuple(uint64 x, KmerPos *a, int n)
{ int l, r, m;


  l = 0;
  r = n;
  while (l < r)
    { m = ((l+r) >> 1);
      if (a[m].code < x)
        l = m+1;
      else
        r = m;
    }
  return (l);
}
