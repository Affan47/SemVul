Rank_SVD(TMatrix X)
{
  PRECISION *d, small;
  int rank, q, err;
  if (!X)
    {
      dw_Error(NULL_ERR);
      return -1;
    }
  q=(ColM(X) < RowM(X)) ? ColM(X) : RowM(X);
  if (!(d=(PRECISION*)dw_malloc(q*sizeof(PRECISION))))
    {
      dw_Error(MEM_ERR);
      return -1;
    }
  if (err=bSVD((PRECISION*)NULL,d,(PRECISION*)NULL,pElementM(X),RowM(X),ColM(X),COLUMN_MAJOR,ROW_MAJOR,MajorForm(X),1))
    {
      dw_free(d);
      dw_Error(err);
      return -1;
    }
  for (small=d[0]*SQRT_MACHINE_EPSILON, rank=q-1; rank >= 0; rank--)
    if (d[rank] > small) break;
  dw_free(d);
  return rank+1;
}
