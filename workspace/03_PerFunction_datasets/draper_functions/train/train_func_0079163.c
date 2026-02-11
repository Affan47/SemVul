pack_reverse_comm(int n, int first, double *buf)
{
  int i,m,last;

  m = 0;
  last = first + n;
  for (i = first; i < last; i++) {
    buf[m++] = partner[i];
    buf[m++] = distsq[i];
  }
  return 2;
}
