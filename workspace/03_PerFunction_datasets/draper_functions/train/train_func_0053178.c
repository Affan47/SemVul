DSDPPassXVectors(DSDP dsdp, double mu, DSDPVec Y, DSDPVec DY){
  int info,kk;
  DSDPFunctionBegin;
  for (kk=0;kk<dsdp->ncones;kk++){
    DSDPEventLogBegin(dsdp->K[kk].coneid);
    info=DSDPConeSetXMaker(dsdp->K[kk].cone,mu,Y,DY);DSDPCHKCONEERR(kk,info);
    DSDPEventLogEnd(dsdp->K[kk].coneid);
  }
  DSDPFunctionReturn(0);
}
