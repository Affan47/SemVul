BConeComputeS(BCone bcone,DSDPVec Y,double ss[], int n){
  int i,ii,info;
  int *ib=bcone->ib, nn=bcone->nn;
  double cr,rr,r,yy,*au=bcone->au,*u=bcone->u;

  DSDPFunctionBegin;
  info=DSDPVecGetC(Y,&cr);
  info=DSDPVecGetR(Y,&rr);
  r=rr*bcone->r;
  for (i=0;i<nn;i++){
    ii=ib[i];
    info=DSDPVecGetElement(Y,ii,&yy);
    ss[i]=-cr*u[i]-au[i]*yy-r;
  }
  DSDPFunctionReturn(0);
}
