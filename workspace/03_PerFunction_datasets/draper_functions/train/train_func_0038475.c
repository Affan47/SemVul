selectpivot (lrs_dic * P, lrs_dat * Q, long *r, long *s)


{
  long j, col;

  lrs_mp_matrix A = P->A;
  long *Col = P->Col;
  long d = P->d;

  *r = 0;
  *s = d;
  j = 0;


  while ((j < d) && (!positive (A[0][Col[j]])))
    j++;

  if (j < d)
    {
      *s = j;
      col = Col[j];


      *r = ratio (P, Q, col);
      if (*r != 0)
	return (TRUE);
    }
  return (FALSE);
}
