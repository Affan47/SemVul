SDPConeComputeX(SDPCone sdpcone, int blockj, int n, double x[], int nn){
  int info;
  double mu=sdpcone->xmakermu;
  double xnorm,xtrace,trxs;
  char UPLQ;
  DSDPVec DY=sdpcone->DYX,Y=sdpcone->YX,AX=sdpcone->Work;
  DSDPVMat T;

  DSDPFunctionBegin;
  info=SDPConeCheckN(sdpcone,blockj,n);DSDPCHKBLOCKERR(blockj,info);
  if (n<1){DSDPFunctionReturn(0);}
  info=SDPConeGetStorageFormat(sdpcone,blockj,&UPLQ);DSDPCHKBLOCKERR(blockj,info);
  info=DSDPMakeVMatWithArray(UPLQ,x,nn,n,&T);DSDPCHKBLOCKERR(blockj,info);
  info=SDPConeComputeX3(sdpcone,blockj,mu,Y,DY,T);DSDPCHKBLOCKERR(blockj,info);
  info=SDPConeComputeXDot(sdpcone,blockj,Y,T,AX,&xtrace,&xnorm,&trxs);DSDPCHKBLOCKERR(blockj,info);
  info=DSDPVMatDestroy(&T);DSDPCHKBLOCKERR(blockj,info);
  DSDPFunctionReturn(0);
}
