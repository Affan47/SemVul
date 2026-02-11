DTPUMatSolve(void* AA, double b[], double x[], int n){
  dtpumat* A=(dtpumat*) AA;
  ffinteger INFO,NRHS=1,LDB=A->n,N=A->n;
  double *AP=A->val,*ss=A->sscale;
  char UPLO=A->UPLO;

  if (N>0) LDB=N;
  dtpuscalevec(1.0,ss,b,x,n);
  dpptrs(&UPLO, &N, &NRHS, AP, x, &LDB, &INFO );
  dtpuscalevec(1.0,ss,x,x,n);
  return INFO;
}
