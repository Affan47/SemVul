DSDPGetRCMat(int n,const double val[],int rowcol, struct  DSDPDataMat_Ops**sops, void**smat){
  rcmat *AA;
  int info;
  DSDPFunctionBegin;
  info=RCMatCreate(n,rowcol,val,&AA);DSDPCHKERR(info);
  info=RCMatOperationsInitialize(&rcmatops); DSDPCHKERR(info);
  if (sops){*sops=&rcmatops;}
  if (smat){*smat=(void*)AA;}
  DSDPFunctionReturn(0);
}
