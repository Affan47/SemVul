LUBoundsSetup2(void *dcone, DSDPVec Y, DSDPSchurMat M){
  int info;
  LUBounds lucone=(LUBounds)dcone;
  DSDPFunctionBegin;
  LUConeValid(lucone);
  if (lucone->setup==0){
    info=DSDPVecDuplicate(Y,&lucone->DYD);DSDPCHKERR(info);
    info=DSDPVecDuplicate(Y,&lucone->YD);DSDPCHKERR(info);
    info=DSDPVecDuplicate(Y,&lucone->YP);DSDPCHKERR(info);
    info=DSDPVecSet(lucone->lbound,lucone->YD);DSDPCHKERR(info);
    info=DSDPVecSetR(lucone->YD,-1e30);DSDPCHKERR(info);
    info=DSDPVecSetC(lucone->YD,-1e30);DSDPCHKERR(info);
    info=DSDPVecPointwiseMax(lucone->YD,Y,Y);DSDPCHKERR(info);
    info=DSDPVecSet(lucone->ubound,lucone->YD);DSDPCHKERR(info);
    info=DSDPVecSetR(lucone->YD,1e30);DSDPCHKERR(info);
    info=DSDPVecSetC(lucone->YD,1e30);DSDPCHKERR(info);
    info=DSDPVecPointwiseMin(lucone->YD,Y,Y);DSDPCHKERR(info);
    lucone->setup=1;
  }
  DSDPFunctionReturn(0);
}
