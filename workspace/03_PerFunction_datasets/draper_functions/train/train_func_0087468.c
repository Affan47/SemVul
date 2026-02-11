ConstMatVecVec(void* A, double x[], int n, double *v){

  cmat* AA = (cmat*)A;
  double dtmp=0.0;
  int i;

  for (i=0; i<n; i++){
    dtmp+=x[i];
  }
  *v=dtmp*dtmp*AA->cnst;
  return 0;
}
