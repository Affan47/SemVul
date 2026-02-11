DTPUMatMult(void* AA, double x[], double y[], int n){
  dtpumat* A=(dtpumat*) AA;
  ffinteger ione=1,N=n;
  double BETA=0.0,ALPHA=1.0;
  double *AP=A->val,*Y=y,*X=x;
  char UPLO=A->UPLO;

  if (A->n != n) return 1;
  if (x==0 && n>0) return 3;
  dspmv(&UPLO,&N,&ALPHA,AP,X,&ione,&BETA,Y,&ione);
  return 0;
}
