R1MatRowNnz(void*A, int row, int nz[], int *rnnz, int n){
  r1mat* AA = (r1mat*)A;
  int i,j;
  int nnz=AA->nnz,ishift=AA->ishift;
  const int *ai=AA->spai;
  *rnnz=0;
  for (i=0;i<nnz;i++){
    if (ai[i]-ishift==row){
      for (j=0;j<nnz;j++){
	nz[ai[j]-ishift]++;
      }
    }
    *rnnz=nnz;
  }
  return 0;
}
