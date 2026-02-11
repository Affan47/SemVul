getbitsfromleaves(const vector<ghnode *> &v) {
  unsigned short nw=0, ne=0, sw=0, se=0 ;
  int i;
  for (i=0; i<(int)v.size(); i++) {
    ghleaf *p = (ghleaf *)v[i] ;
    nw |= p->nw ;
    ne |= p->ne ;
    sw |= p->sw ;
    se |= p->se ;
  }
  int r = 0 ;

  unsigned short w = nw | sw ;
  unsigned short e = ne | se ;

  unsigned short n = nw | ne ;
  unsigned short s = sw | se ;
  if (w)
    r |= 512 ;
  if (e)
    r |= 256 ;
  if (n)
    r |= 2 ;
  if (s)
    r |= 1 ;
  return r ;
}
