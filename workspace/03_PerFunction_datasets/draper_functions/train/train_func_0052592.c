DSDPSetDefaultStatistics(DSDP dsdp){

  int i;
  DSDPFunctionBegin;
  DSDPValid(dsdp);
  dsdp->reason=CONTINUE_ITERATING;
  dsdp->pdfeasible=DSDP_PDUNKNOWN;
  dsdp->itnow=0;
  dsdp->pobj=  1.0e10;
  dsdp->ppobj=  1.0e10;
  dsdp->dobj= -1.0e+9;
  dsdp->ddobj= -1.0e+9;
  dsdp->dualitygap=dsdp->ppobj-dsdp->ddobj;
  dsdp->pstep=1.0;
  dsdp->dstep=0.0;
  for (i=0;i<MAX_XMAKERS;i++){
    dsdp->xmaker[i].mu=1.0e200;
    dsdp->xmaker[i].pstep=0.0;
  }
  dsdp->pnorm=0.001;
  dsdp->mu=1000.0;
  dsdp->np=0;
  dsdp->anorm=0;
  dsdp->bnorm=0;
  dsdp->cnorm=0;
  dsdp->tracex=0;
  dsdp->tracexs=0;
  dsdp->Mshift=0;
  dsdp->goty0=DSDP_FALSE;
  DSDPFunctionReturn(0);
}
