unpack_exchange(int nlocal, double *buf)
{


  int m = 0;
  npartner[nlocal] = static_cast<int> (buf[m++]);
  maxtouch = MAX(maxtouch,npartner[nlocal]);
  partner[nlocal] = ipage->get(npartner[nlocal]);
  shearpartner[nlocal] = dpage->get(npartner[nlocal]);
  for (int n = 0; n < npartner[nlocal]; n++) {
    partner[nlocal][n] = static_cast<int> (buf[m++]);
    shearpartner[nlocal][n][0] = buf[m++];
    shearpartner[nlocal][n][1] = buf[m++];
    shearpartner[nlocal][n][2] = buf[m++];
  }
  return m;
}
