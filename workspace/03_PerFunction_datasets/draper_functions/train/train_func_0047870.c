CountNonzeros(DSDPBlockData *ADATA,int m, int rnnz[], int innz[],int n,int *nnz1, int *nnz2)
{
  int i,j,info,totalnnz1=0,totalnnz2=0;

  for (i=0;i<n;i++){
    memset(rnnz,0,n*sizeof(int));

    for (j=0;j<m;j++) innz[j]=1;innz[0]=0;
    info=DSDPBlockDataRowSparsity(ADATA,i,innz,rnnz,n);DSDPCHKERR(info);
    for (j=0; j<i; j++){ if (rnnz[j]>0) totalnnz1++;}

    for (j=0;j<m;j++) innz[j]=0;innz[0]=1;
    info=DSDPBlockDataRowSparsity(ADATA,i,innz,rnnz,n);DSDPCHKERR(info);
    for (j=0; j<i; j++){ if (rnnz[j]>0) totalnnz2++;}
  }
  *nnz1=totalnnz1;
  *nnz2=totalnnz2;
  return 0;
}
