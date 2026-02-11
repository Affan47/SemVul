DvecumatView(void* AA){
  dvecumat* A=(dvecumat*)AA;
  dtrumat* M=A->AA;
  int i,j,LDA=M->LDA;
  double *val=M->val;
  for (i=0; i<M->n; i++){
    for (j=0; j<M->n; j++){
      printf(" %4.2e",val[j]);
    }
    val+=LDA;
  }
  return 0;
}
