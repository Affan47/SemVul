unpack_comm(int n, int first, double *buf)
{
  int i,m,last;

  m = 0;
  last = first + n;
  for (i = first; i < last; i++) {
    fp[i] = buf[m++];
    mu[i][0] = buf[m++];
    mu[i][1] = buf[m++];
    mu[i][2] = buf[m++];
    lambda[i][0] = buf[m++];
    lambda[i][1] = buf[m++];
    lambda[i][2] = buf[m++];
    lambda[i][3] = buf[m++];
    lambda[i][4] = buf[m++];
    lambda[i][5] = buf[m++];
  }
}
