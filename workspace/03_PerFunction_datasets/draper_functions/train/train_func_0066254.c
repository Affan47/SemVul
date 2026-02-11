DSDPLAPACKPUDualMatCreate(int n,struct  DSDPDualMat_Ops **sops, void**smat){
  int info,nn=n*(n+1)/2;
  double *vv;
  dtpumat*AA;
  DSDPFunctionBegin;
  DSDPCALLOC2(&vv,double,nn,&info);DSDPCHKERR(info);
  info=DTPUMatCreateWData(n,vv,nn,&AA); DSDPCHKERR(info);
  AA->owndata=1;;
  AA->scaleit=1;
  info=SDualOpsInitialize(&sdmatops);DSDPCHKERR(info);
  *sops=&sdmatops;
  *smat=(void*)AA;
  DSDPFunctionReturn(0);
}
