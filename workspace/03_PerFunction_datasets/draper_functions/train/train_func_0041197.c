DSDPGetTraceX(DSDP dsdp, double *tracex){
  DSDPFunctionBegin;
  DSDPValid(dsdp);
  *tracex=dsdp->tracex;
  DSDPFunctionReturn(0);
}
