DSDPVecISet(int* ival,DSDPVec V){
  int i;
  for (i=0;i<V.dim;i++){
    V.val[i]=ival[i];
  }
  return 0;
}
