MatZeroEntries4(chfac *sf){

  int i,n=sf->n;
  double *rw=sf->rw;
  memset((void*)(sf->diag),0,n*sizeof(double));
  memset((void*)(rw),0,n*sizeof(double));

  for (i=0; i<n; i++){
    setColi(sf,i,rw);
  }

  return 0;
}
