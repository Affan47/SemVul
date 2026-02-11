DSDPDualMatSetArray(DSDPDualMat S, DSDPVMat T){
  double *ss;
  int info,n,nn;
  DSDPFunctionBegin;
  if (S.dsdpops->matseturmat){
    info=DSDPVMatGetSize(T,&n); DSDPCHKERR(info);
    info=DSDPVMatGetArray(T,&ss,&nn); DSDPCHKERR(info);
    info=(S.dsdpops->matseturmat)(S.matdata,ss,nn,n); DSDPChkDMatError(S,info);
    info=DSDPVMatRestoreArray(T,&ss,&nn); DSDPCHKERR(info);
  } else {
    DSDPNoOperationError(S);
  }
  DSDPFunctionReturn(0);
}
