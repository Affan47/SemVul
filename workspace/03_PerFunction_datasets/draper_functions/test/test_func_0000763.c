bProductMT(PRECISION *x, PRECISION *y, int m, int n, int u, int xt, int yt)
{
#if PRECISION_SIZE == 4
  #define trmm strmm
#else
  #define trmm dtrmm
#endif

  char side, uplo, transa, diag='N';
  PRECISION alpha=1.0;
  blas_int bm=m, bn=n;

  if (xt)
    {
      side='R';
      if (yt) {transa='N'; uplo=u ? 'U' : 'L';} else {transa='T'; uplo=u ? 'L' : 'U';}
      trmm(&side,&uplo,&transa,&diag,&bm,&bn,&alpha,y,&bn,x,&bm);
    }
  else
    {
      side='L';
      if (yt) {transa='T'; uplo=u ? 'U' : 'L';} else {transa='N'; uplo=u ? 'L' : 'U';}
      trmm(&side,&uplo,&transa,&diag,&bn,&bm,&alpha,y,&bn,x,&bn);
    }
  return NO_ERR;

#undef trmm
}
