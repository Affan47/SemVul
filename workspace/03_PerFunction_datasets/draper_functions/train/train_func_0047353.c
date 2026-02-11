DTRUMatSetXMat(void*A, double v[], int nn, int n){
  dtrumat*  ABA=(dtrumat*)A;
  int i,LDA=ABA->LDA;
  double *vv=ABA->val;
  if (vv!=v){
    for (i=0;i<n;i++){
      memcpy((void*)vv,(void*)v,(i+1)*sizeof(double));
      vv+=LDA; v+=n;
    }
  }
  ABA->status=Assemble;
  return 0;
}
