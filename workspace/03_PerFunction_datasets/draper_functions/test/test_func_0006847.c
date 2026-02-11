DSDPSchurMatSolveM(DSDPSchurMat M, DSDPVec b, DSDPVec x){
  int info,n;
  double *xx,*bb;
  DSDPFunctionBegin;
  info=DSDPEventLogBegin(hsolveevent);
  if (M.dsdpops->matsolve){
    info=DSDPVecGetArray(b,&bb); DSDPCHKERR(info);
    info=DSDPVecGetSize(x,&n); DSDPCHKERR(info);
    info=DSDPVecZero(x);DSDPCHKERR(info);
    info=DSDPVecGetArray(x,&xx); DSDPCHKERR(info);
    info=(M.dsdpops->matsolve)(M.data,bb+1,xx+1,n-2); DSDPChkMatError(M,info);
    info=DSDPVecRestoreArray(b,&bb); DSDPCHKERR(info);
    info=DSDPVecRestoreArray(x,&xx); DSDPCHKERR(info);
  } else {
    DSDPNoOperationError(M);
  }
  info=DSDPVecSetR(x,0.0);DSDPCHKERR(info);
  info=DSDPVecSetC(x,0.0);DSDPCHKERR(info);
  info=DSDPEventLogEnd(hsolveevent);
  DSDPFunctionReturn(0);
}
