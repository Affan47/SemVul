skip()
{


  int nchunk;
  bigint nremain = natoms;
  while (nremain) {
    nchunk = MIN(nremain,MAXSMALLINT);
    read_lines(nchunk);
    nremain -= nchunk;
  }
}
