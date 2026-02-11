R1MatAddRowMultiple(void*A, int nrow, double dd, double row[], int n){
  r1mat* AA = (r1mat*)A;
  int nnz=AA->nnz,ishift=AA->ishift;
  const int *ai=AA->spai;
  const double *val=AA->spval;
  double ddd=dd*AA->ev;
  int i,j;
  for (i=0;i<nnz;i++){
    if (ai[i]-ishift==nrow){
      for (j=0;j<nnz;j++){
	row[ai[j]-ishift]+= ddd*val[i]*val[j];
      }
    }
  }
  return 0;
}
