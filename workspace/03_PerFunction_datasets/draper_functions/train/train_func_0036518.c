compmin(node *p, node *desc)
{

  long i, j, minn, cost, desclen, descrecon=0, maxx;

  maxx = 10 * spp;
  for (i = (long)A; i <= (long)O; i++) {
    minn = maxx;
    for (j = (long)A; j <= (long)O; j++) {
      if (transvp) {
        if (
               (
                ((i == (long)A) || (i == (long)G))
             && ((j == (long)A) || (j == (long)G))
               )
            || (
                ((j == (long)C) || (j == (long)T))
             && ((i == (long)C) || (i == (long)T))
               )
           )
          cost = 0;
        else
          cost = 1;
      } else {
        if (i == j)
          cost = 0;
        else
          cost = 1;
      }
      if (desc->cumlengths[j] == -1) {
        desclen = maxx;
      } else {
        desclen = desc->cumlengths[j];
      }
      if (minn > cost + desclen) {
        minn = cost + desclen;
        descrecon = 0;
      }
      if (minn == cost + desclen) {
        descrecon += desc->numreconst[j];
      }
    }
    p->cumlengths[i] += minn;
    p->numreconst[i] *= descrecon;
  }
  p->initialized = true;
}
