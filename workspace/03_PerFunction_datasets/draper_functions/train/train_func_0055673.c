SDPConeComputeXDot(SDPCone sdpcone, int blockj, DSDPVec Y,DSDPVMat X, DSDPVec AX, double* xtrace,double *xnorm, double *tracexs){
  int info;
  SDPblk *blk=sdpcone->blk;
  DSDPVec YW2=sdpcone->Work2;
  double one=1.0,scl=blk[blockj].ADATA.scl;
  DSDPFunctionBegin;
  info=DSDPVecZero(YW2);DSDPCHKBLOCKERR(blockj,info);
  info=DSDPBlockADot(&blk[blockj].ADATA,-1.0/scl,Y,X,YW2);DSDPCHKBLOCKERR(blockj,info);
  info=DSDPVecGetR(YW2,xtrace);DSDPCHKBLOCKERR(blockj,info);
  info=DSDPVecSum(YW2,tracexs);DSDPCHKBLOCKERR(blockj,info);
  info=DSDPVMatNormF2(X,xnorm);DSDPCHKBLOCKERR(blockj,info);
  info=DSDPVecSet(one,YW2);DSDPCHKBLOCKERR(blockj,info);
  info=DSDPBlockADot(&blk[blockj].ADATA,1.0/scl,YW2,X,AX);DSDPCHKBLOCKERR(blockj,info);
  DSDPFunctionReturn(0);
}
