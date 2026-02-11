DTRUMatMultR(void* AA, double x[], double y[], int n){
  dtrumat* A=(dtrumat*) AA;
  ffinteger N=n,LDA=A->LDA,INCX=1,INCY=1;
  double ALPHA=1.0;
  double *AP=A->val,*Y=y,*X=x,*ss=A->sscale,*W=A->workn;
  char UPLO=A->UPLO,TRANS='N',DIAG='U';

  UPLO='L';
  if (A->n != n) return 1;
  if (x==0 && n>0) return 3;


  memset(y,0,n*sizeof(double));

  memcpy(W,X,n*sizeof(double));
  TRANS='N'; UPLO='L';
  dtrmv(&UPLO,&TRANS,&DIAG,&N,AP,&LDA,W,&INCY);
  daxpy(&N,&ALPHA,W,&INCX,Y,&INCY);

  memcpy(W,X,n*sizeof(double));
  TRANS='T'; UPLO='L';
  dtrmv(&UPLO,&TRANS,&DIAG,&N,AP,&LDA,W,&INCY);
  daxpy(&N,&ALPHA,W,&INCX,Y,&INCY);

  dsydadd(x,ss,y,n);
  return 0;
}
