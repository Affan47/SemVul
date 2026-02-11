DSDPSchurMatFactor(DSDPSchurMat M, DSDPTruth *successful){
  int info,flag=0;
  DSDPVec rhs3=M.schur->rhs3,dy3=M.schur->dy3;
  DSDPFunctionBegin;
  *successful=DSDP_TRUE;
  DSDPEventLogBegin(hfactorevent);
  if (M.dsdpops->matfactor){
    info=(M.dsdpops->matfactor)(M.data,&flag); DSDPChkMatError(M,info);
    if (flag){
      *successful=DSDP_FALSE;
      DSDPLogInfo(0,2,"Indefinite Schur Matrix -- Bad Factorization\n");
    }
  } else {
    DSDPNoOperationError(M);
  }
  DSDPEventLogEnd(hfactorevent);
  if (M.schur->r){
    info=DSDPSchurMatSolveM(M,rhs3,dy3);DSDPCHKERR(info);}
  else {info=DSDPVecZero(dy3);DSDPCHKERR(info);}
  DSDPFunctionReturn(0);
}
