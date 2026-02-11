ismin (lrs_dic * P, lrs_dat * Q, long r, long s)

{
  long i;

  lrs_mp_matrix A = P->A;
  long m_A = P->m_A;

  for (i = 1; i <= m_A; i++)
    if ((i != r) &&
	negative (A[i][s]) && comprod (A[i][0], A[r][s], A[i][s], A[r][0]))
      {
	return (FALSE);
      }

  return (TRUE);
}
