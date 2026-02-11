DSDPVMatMinEigenvalue(DSDPVMat X, SDPConeVec W1, SDPConeVec W2, double *mineig){
  int n,info;
  double *w,*iwork;
  DSDPFunctionBegin;
  if (X.dsdpops->matmineig){
    info=SDPConeVecGetSize(W1,&n); DSDPCHKERR(info);
    info=SDPConeVecGetArray(W1,&w); DSDPCHKERR(info);
    info=SDPConeVecGetArray(W2,&iwork); DSDPCHKERR(info);
    info=(X.dsdpops->matmineig)(X.matdata,w,iwork,n,mineig); DSDPChkMatError(X,info);
    info=SDPConeVecRestoreArray(W1,&w); DSDPCHKERR(info);
    info=SDPConeVecRestoreArray(W2,&iwork); DSDPCHKERR(info);
  } else {
    DSDPNoOperationError(X);
  }
  DSDPFunctionReturn(0);
}
