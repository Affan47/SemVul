unpack_exchange(int nlocal, double *buf)
{
  int m = 0;
  npartner[nlocal] = static_cast<int> (buf[m++]);
  for (int n = 0; n < npartner[nlocal]; n++) {
    partner[nlocal][n] = static_cast<int> (buf[m++]);
    if (isVES) {
      deviatorextention[nlocal][n] = buf[m++];
      deviatorBackextention[nlocal][n] = buf[m++];
    }
    r0[nlocal][n] = buf[m++];
  }
  vinter[nlocal] = buf[m++];
  wvolume[nlocal] = buf[m++];
  return m;
}
