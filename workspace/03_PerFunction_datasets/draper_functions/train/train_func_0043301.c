xsplit (mp, nu)
     union mhead *mp;
     int nu;
{
  union mhead *nh;
  int nbuck, nblks, split_max;
  unsigned long siz;

  nbuck = nu - 1;
  while (nbuck >= SPLIT_MIN && busy[nbuck])
    nbuck--;
  if (nbuck < SPLIT_MIN)
    return;

#ifdef MALLOC_STATS
  _mstats.tbsplit++;
  _mstats.nsplit[nu]++;
#endif


  siz = binsize (nu);
  nblks = siz / binsize (nbuck);


  siz = binsize (nbuck);
  nh = mp;
  while (1)
    {
      mp->mh_alloc = ISFREE;
      mp->mh_index = nbuck;
      if (--nblks <= 0) break;
      CHAIN (mp) = (union mhead *)((char *)mp + siz);
      mp = (union mhead *)((char *)mp + siz);
    }
  busy[nbuck] = 1;
  CHAIN (mp) = nextf[nbuck];
  nextf[nbuck] = nh;
  busy[nbuck] = 0;
}
