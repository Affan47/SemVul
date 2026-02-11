DSDPDualMatInverseAdd(DSDPDualMat S, double alpha, DSDPVMat T){
  int info,n,nn;
  double *ss;
  DSDPFunctionBegin;
  if (S.dsdpops->matinverseadd){
    info=DSDPVMatGetSize(T,&n); DSDPCHKERR(info);
    info=DSDPVMatGetArray(T,&ss,&nn); DSDPCHKERR(info);
    info=(S.dsdpops->matinverseadd)(S.matdata,alpha,ss,nn,n); DSDPChkDMatError(S,info);
    info=DSDPVMatRestoreArray(T,&ss,&nn); DSDPCHKERR(info);
  } else {
    DSDPNoOperationError(S);
  }
  DSDPFunctionReturn(0);
}
