signed_cmp(coord c1, coord c2)
{
  if (c1.i > c2.i) return 1;
  else if (c1.i < c2.i) return -1;
  else return 0;
}
