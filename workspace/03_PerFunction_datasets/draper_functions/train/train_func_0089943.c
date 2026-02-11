DSDPCreateLPCone(DSDP dsdp, LPCone *dspcone){
  int m,info;
  struct LPCone_C *lpcone;
  DSDPFunctionBegin;
  DSDPCALLOC1(&lpcone,struct LPCone_C,&info);DSDPCHKERR(info);
  *dspcone=lpcone;


  info=LPConeOperationsInitialize(&kops); DSDPCHKERR(info);
  info=DSDPAddCone(dsdp,&kops,(void*)lpcone); DSDPCHKERR(info);
  info=DSDPGetNumberOfVariables(dsdp,&m);DSDPCHKERR(info);
  lpcone->m=m;
  lpcone->muscale=1.0;
  lpcone->n=0;
  lpcone->xout=0;
  lpcone->r=1.0;
  info=DSDPVecCreateSeq(0,&lpcone->C);DSDPCHKERR(info);
  info=DSDPVecCreateSeq(0,&lpcone->WY);DSDPCHKERR(info);
  info=DSDPVecDuplicate(lpcone->C,&lpcone->WX);DSDPCHKERR(info);
  info=DSDPVecDuplicate(lpcone->C,&lpcone->WX2);DSDPCHKERR(info);
  info=DSDPVecDuplicate(lpcone->C,&lpcone->PS);DSDPCHKERR(info);
  info=DSDPVecDuplicate(lpcone->C,&lpcone->DS);DSDPCHKERR(info);
  info=DSDPVecDuplicate(lpcone->C,&lpcone->X);DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
