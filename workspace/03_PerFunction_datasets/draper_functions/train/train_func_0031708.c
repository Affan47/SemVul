DSDPVMatDestroy(DSDPVMat *X){
  int info;
  DSDPFunctionBegin;
  if (!(*X).dsdpops){ return 0;}
  if ((*X).dsdpops->matdestroy){
    info=((*X).dsdpops->matdestroy)((*X).matdata); DSDPChkMatError(*X,info);
  } else {

  }
  info=DSDPVMatInitialize(X); DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
