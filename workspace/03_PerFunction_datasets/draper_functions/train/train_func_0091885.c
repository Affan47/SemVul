DTRUMatMult(void* AA, double x[], double y[], int n){
  dtrumat* A=(dtrumat*) AA;
  ffinteger N=n,LDA=A->LDA,INCX=1,INCY=1;
  double BETA=0.0,ALPHA=1.0;
  double *AP=A->val,*Y=y,*X=x;
  char UPLO=A->UPLO,TRANS='N';

  if (A->n != n) return 1;
  if (x==0 && n>0) return 3;
  if (0==1){
    dgemv(&TRANS,&N,&N,&ALPHA,AP,&LDA,X,&INCX,&BETA,Y,&INCY);
  } else {
    dsymv(&UPLO,&N,&ALPHA,AP,&LDA,X,&INCX,&BETA,Y,&INCY);
  }
  return 0;
}
