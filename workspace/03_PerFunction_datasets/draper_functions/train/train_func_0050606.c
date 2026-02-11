nuview(node *p)
{

  long i, j, k, lowlim;
  double sumq;
  node *q, *s;

  if (p->tip)
    return false;
  for (s = p->next; s != p; s = s->next) {
    if ( nuview(s->back) )
      p->initialized = false;
  }

  if (p->initialized)
    return false;

  lowlim = trunc8 ? 0 : 1;


  for (i = lowlim; i <= endsite; i++) {
    for (j = 0; j <= sitelength; j++)
      p->x2[i][j] = 1.0;
    for (s = p->next; s != p; s = s->next) {
      q = s->back;
      for (j = 0; j <= sitelength; j++) {
        sumq = 0.0;
        for (k = 0; k <= sitelength; k++)
          sumq += curtree.trans[q->branchnum-1][j][k] * q->x2[i][k];
        p->x2[i][j] *= sumq;
      }
    }
  }

  return true;
}
