DTPUMatShiftDiagonal(void* AA, double shift){
  dtpumat* A=(dtpumat*) AA;
  int i,n=A->n;
  double *v=A->val;
  for (i=0; i<n; i++){
    *v+=shift;
    v+=i+2;
  }
  return 0;
}
