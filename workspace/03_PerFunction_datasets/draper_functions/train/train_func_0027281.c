DSDPSchurMatDiagonalScaling(DSDPSchurMat M, DSDPVec D){
  int m,info;
  double *vars;
  DSDPTruth flag;
  DSDPFunctionBegin;
  info=DSDPVecSet(1.0,D);DSDPCHKERR(info);
  info=DSDPVecGetSize(D,&m);DSDPCHKERR(info);
  if (M.dsdpops->pmatlocalvariables){
    info=DSDPVecGetArray(D,&vars);DSDPCHKERR(info);
    info=(M.dsdpops->pmatlocalvariables)(M.data,vars+1,m-2); DSDPChkMatError(M,info);
    info=DSDPVecRestoreArray(D,&vars);DSDPCHKERR(info);
  } else {
    info=DSDPSchurMatInParallel(M,&flag);DSDPChkMatError(M,info);
    if (flag==DSDP_TRUE){
      DSDPNoOperationError(M);
    }
  }
  info=DSDPVecSetC(D,0.0);DSDPCHKERR(info);
  if (M.schur->r==0){info=DSDPVecSetR(D,0.0);DSDPCHKERR(info);}
  info=DSDPZeroFixedVariables(M,D);DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
