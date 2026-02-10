sparse_matvec( sparse_matrix *A, double *x, double *b )
{
  int i, j, itr_j;

  for( i = 0; i < n; ++i )
    b[i] = eta[ atom->type[i] ] * x[i];
  for( i = n; i < N; ++i )
    b[i] = 0;

  for( i = 0; i < n; ++i ) {
    for( itr_j=A->firstnbr[i]; itr_j<A->firstnbr[i]+A->numnbrs[i]; itr_j++) {
      j = A->jlist[itr_j];
      b[i] += A->val[itr_j] * x[j];
      b[j] += A->val[itr_j] * x[i];
    }
  }
}
