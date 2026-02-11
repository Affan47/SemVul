DvechmatFNorm2(void* AA, int n, double *v){
  dvechmat* A=(dvechmat*)AA;
  long int i,j,k=0;
  double dd=0,*x=A->AA->val;
  for (i=0; i<n; i++){
    for (j=0;j<i;j++){
      dd+=2*x[k]*x[k];
      k++;
    }
    dd+=x[k]*x[k];
    k++;
  }
  *v=dd*A->alpha*A->alpha;
  return 0;
}
