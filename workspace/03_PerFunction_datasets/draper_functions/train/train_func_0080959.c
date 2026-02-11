CreateS1b(DSDPBlockData *ADATA, int innz[], int m, int n, int tnnz[], int rnnz[], int snnz[])
{
  int i,j,info;
  if (ADATA->nnzmats<=0){return 0;};

  memset(rnnz,0,n*sizeof(int));
  for (i=0;i<m;i++) innz[i]=1;
  innz[0]=0;


  for (i=0;i<n;i++){
    memset(tnnz,0,n*sizeof(int));
    info=DSDPBlockDataRowSparsity(ADATA,i,innz,tnnz,n);DSDPCHKERR(info);
    for (j=0; j<=i; j++){
      if (tnnz[j]>0){ *snnz=j; snnz++; rnnz[i]++;}
    }
  }
  return 0;
}
