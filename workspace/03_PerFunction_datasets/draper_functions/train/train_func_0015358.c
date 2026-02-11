BConeSetLowerBound(BCone bcone,int vari, double lbound){
  int info;
  DSDPFunctionBegin;
  info=BConeSetBound(bcone,vari,-1.0,-lbound);DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
