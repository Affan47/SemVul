DTPUMatCholeskyFactor(void* AA, int *flag){
  dtpumat* A=(dtpumat*) AA;
  int i;
  ffinteger INFO,LDA=1,N=A->n;
  double *AP=A->val,*ss=A->sscale,*v;
  char UPLO=A->UPLO;

  if (N<=0) LDA=1;
  else LDA=N;
  if (A->scaleit){
    for (v=AP,i=0;i<N;i++){ ss[i]=*v;v+=(i+2);}
    for (i=0;i<N;i++){ ss[i]=1.0/sqrt(fabs(ss[i])+1.0e-8); }
    dtpuscalemat(AP,ss,N);
  }
  dpptrf(&UPLO, &N, AP, &INFO );
  *flag=INFO;
  return 0;
}
