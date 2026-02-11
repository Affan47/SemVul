DSDPGetRR(DSDP dsdp,double *res){
  int info;
  DSDPFunctionBegin;
  DSDPValid(dsdp);
  info=DSDPVecGetR(dsdp->y,res);DSDPCHKERR(info);
  *res=-*res;
  if (*res==0) *res=0;
  DSDPFunctionReturn(0);
}
