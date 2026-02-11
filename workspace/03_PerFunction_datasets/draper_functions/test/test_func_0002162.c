SDPConeViewX(SDPCone sdpcone, int blockj, int n, double x[], int nn){
  int info;
  char UPLQ;
  DSDPVMat T;

  DSDPFunctionBegin;
  info=SDPConeCheckN(sdpcone,blockj,n);DSDPCHKBLOCKERR(blockj,info);
  info=SDPConeGetStorageFormat(sdpcone,blockj,&UPLQ);DSDPCHKBLOCKERR(blockj,info);
  info=DSDPMakeVMatWithArray(UPLQ,x,nn,n,&T);DSDPCHKBLOCKERR(blockj,info);
  info=DSDPVMatView(T);DSDPCHKBLOCKERR(blockj,info);
  info=DSDPVMatDestroy(&T);DSDPCHKBLOCKERR(blockj,info);
  DSDPFunctionReturn(0);
}
