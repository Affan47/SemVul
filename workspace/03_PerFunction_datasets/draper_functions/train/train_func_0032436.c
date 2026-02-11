gpi_sym(I key, A aobj)
{
  I i, tt;
  A t0, t1;
  if (Et != aobj->t || 2 != aobj->n) {q=ERR_DOMAIN;R -1;}
  t0=(A)aobj->p[0]; t1=(A)aobj->p[1];
  if ((!QA(t0))||(!QA(t1))||Et!=t1->t||t0->n!=t1->n) {q=ERR_DOMAIN;R -1;}
  for (i=0;i<t0->n;++i) {
    tt=t0->p[i];
    if (!QS(tt)) {q=ERR_DOMAIN;R -1;}
    if (key==tt) R i;
  }
  q=ERR_INDEX;R -1;
}
