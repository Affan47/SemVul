DSDPSetupBCone2(void* dspcone, DSDPVec y, DSDPSchurMat M){
  BDCone *K=(BDCone*)dspcone;
  int info;
  DSDPFunctionBegin;
  info=DSDPVecDuplicate(K->b,&K->T);DSDPCHKERR(info);
  info=DSDPVecDuplicate(K->b,&K->bb);DSDPCHKERR(info);
  info=DSDPSetDRData(K);DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
