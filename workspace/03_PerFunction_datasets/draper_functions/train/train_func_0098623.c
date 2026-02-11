ztrans(fftw_complex *a, fftw_complex *b, int n1, int n2) {
  int ii, jj, i, j;
  int tmin1, tmin2;
  int lda, ldb;

  lda = n1;
  ldb = n2;

#ifdef _OPENMP
#pragma omp parallel for private(i,j,jj,tmin1,tmin2)
#endif
  for (ii = 0; ii < n1; ii += FFTE_NBLK)
    for (jj = 0; jj < n2; jj += FFTE_NBLK) {

      V3MIN( tmin1, ii + FFTE_NBLK, n1 );
      for (i = ii; i < tmin1; ++i) {

        V3MIN( tmin2, jj + FFTE_NBLK, n2 );
        for (j = jj; j < tmin2; ++j) {
          c_assgn( ARR2D( b, j, i, ldb ), ARR2D( a, i, j, lda ) );
        }
      }
    }
}
