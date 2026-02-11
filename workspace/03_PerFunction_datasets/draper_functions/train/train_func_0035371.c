bf_testlfn(bloomfilter_t *bf, char *lfn)

{
  int	i;
  u_int	h;
  u_int	m;
  u_int	idx;
  u_int	offset;

  if (!bf->bfsize)
    return 0;
  for (i = 0; i < bf->numhash; i++) {
    h = bfhash(lfn, shifts[i]);
    m = h % bf->bfsize;
    idx = m / 8;
    offset = m % 8;
    if (!(bf->bits[idx] & (1 << (7 - offset))))
      return 0;
  }
  return 1;
}
