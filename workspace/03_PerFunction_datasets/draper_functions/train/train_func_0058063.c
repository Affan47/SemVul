DSDPVecReciprocalSqrt(DSDPVec V){

  int i,n=V.dim;
  double *val=V.val;

  for (i=0; i<n; i++){
    val[i]= sqrt(1.0/val[i]);
  }

  return 0;
}
