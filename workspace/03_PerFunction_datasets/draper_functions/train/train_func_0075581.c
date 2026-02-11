DSDPSetStandardMonitor(DSDP dsdp, int k){
  int info;
  info=DSDPSetMonitor(dsdp,DSDPPrintStats,0); DSDPCHKERR(info);
  dsdpprintlevel=k;
  return (0);
}
