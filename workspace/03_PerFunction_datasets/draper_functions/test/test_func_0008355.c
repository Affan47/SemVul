SMatInverseAddP(void *S, double alpha, double v[], int nn, int n){
  spmat* SS=(spmat*)S;
  ffinteger ii,ione=1;
  double *x,*b,*ss=SS->sinv;
  int i,j,k=0;

  if (ss){
    for (i=0;i<n;i++){
      v+=i; ii=i+1;
      daxpy(&ii,&alpha,ss,&ione,v,&ione);
      ss+=n;
    }
  } else {
    b=SS->spsym->rw;x=b+n;
    for (i=0;i<n;i++){
      memset((void*)b,0,n*sizeof(double));
      b[i]=alpha;
      ChlSolve(SS->spsym, b, x);
      k=k+i;
      for (j=0;j<=i;j++){
	v[k+j]+=x[j];
      }
    }
  }
  return 0;
}
