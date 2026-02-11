VechMatView(void* AA){
  vechmat* A=(vechmat*)AA;
  int info,i=0,j,k,rank=0,ishift=A->ishift,n=A->n,nnz=A->nnzeros;
  const int *ind=A->ind;
  const double *val=A->val;
  for (k=0; k<nnz; k++){
    getij(ind[k]-ishift,n,&i,&j);
    printf("Row: %d, Column: %d, Value: %10.8f \n",i,j,A->alpha*val[k]);
  }
  if (A->factored>0){
    info=VechMatGetRank(AA,&rank,n);DSDPCHKERR(info);
    printf("Detected Rank: %d\n",rank);
  }
  return 0;
}
