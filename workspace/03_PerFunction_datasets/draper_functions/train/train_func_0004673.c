EigMatSetEig(Eigen* A,int row, double eigv, int idxn[], double v[], int nsub,int n){
  int j,k,*cols=A->cols;
  double *an=A->an;

  A->eigval[row]=eigv;
  if (cols){
    k=0; if (row>0){ k=A->nnz[row-1];}
    cols+=k; an+=k;
    for (k=0,j=0; j<nsub; j++){
      if (v[j]==0.0) continue;
      cols[k]=idxn[j]; an[k]=v[j]; k++;
    }
  } else {
    an+=n*row;
    for (j=0; j<nsub; j++){
      if (v[j]==0.0) continue;
      an[idxn[j]]=v[j];
    }
  }
  return 0;
}
