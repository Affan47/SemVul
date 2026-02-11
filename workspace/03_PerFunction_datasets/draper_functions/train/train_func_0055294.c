bSolveUnitTriangular(PRECISION *a, PRECISION *b, int m, int n, int u, int at, int bt)
{
#if PRECISION_SIZE == 4
  #define trsm strsm
#else
  #define trsm dtrsm
#endif

  PRECISION alpha=1.0;
  char diag='U', side, transa, uplo;
  blas_int bi, bm=m, bn=n;

  if (bt)
    {
      bi=bm; side='L';
      if (at) { transa='N'; uplo=u ? 'U' : 'L'; } else { transa='T'; uplo=u ? 'L' : 'U';}
    }
  else
    {
      bi=bn; bn=bm; side='R';
      if (at) { transa='T'; uplo=u ? 'U' : 'L'; } else { transa='N'; uplo=u ? 'L' : 'U'; }
    }

  trsm(&side,&uplo,&transa,&diag,&bi,&bn,&alpha,a,&bm,b,&bi);

  return NO_ERR;

#undef trsm
}
