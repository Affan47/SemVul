DPrintMatrix(char UPLQ, int constraint, int block, double amat[], int n, FILE*fp){
  if (UPLQ=='P'){
    DPrintUpperRightMatrix(constraint,block,amat,n,fp);
  } else if (UPLQ=='U'){
    DPrintUpperFullMatrix(constraint,block,amat,n,fp);
  }
  return;
}
