DSDPDualMatCholeskyFactor(DSDPDualMat S,DSDPTruth *psdefinite){
  int info;
  int flag;
  DSDPFunctionBegin;
  if (S.dsdpops->matcholesky){
    info=(S.dsdpops->matcholesky)(S.matdata,&flag); DSDPChkDMatError(S,info);
  } else {
     DSDPNoOperationError(S);
  }
  if (flag) *psdefinite=DSDP_FALSE;
  else  *psdefinite=DSDP_TRUE;
  DSDPFunctionReturn(0);
}
