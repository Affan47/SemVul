DSDPSchurMatMultR(DSDPSchurMat M, DSDPVec x, DSDPVec y){
  int info,n;
  double *xx,*yy,r=M.schur->r;
  double r1,r2,dd;
  DSDPVec rhs3;
  DSDPFunctionBegin;

  if (M.dsdpops->matmultr){
    info=DSDPVecGetSize(x,&n); DSDPCHKERR(info);
    info=DSDPVecGetArray(x,&xx); DSDPCHKERR(info);
    info=DSDPVecGetArray(y,&yy); DSDPCHKERR(info);
    info=(M.dsdpops->matmultr)(M.data,xx+1,yy+1,n-2); DSDPChkMatError(M,info);
    yy[0]=0;
    yy[n-1]=0;
    info=DSDPVecRestoreArray(y,&yy); DSDPCHKERR(info);
    info=DSDPVecRestoreArray(x,&xx); DSDPCHKERR(info);
    if (r){
      rhs3=M.schur->rhs3;
      info=DSDPVecGetR(rhs3,&r2);DSDPCHKERR(info);
      info=DSDPVecGetR(x,&r1);DSDPCHKERR(info);
      info=DSDPVecAXPY(r1,rhs3,y);DSDPCHKERR(info);
      info=DSDPVecDot(rhs3,x,&dd);DSDPCHKERR(info);
      info=DSDPVecAddR(y,dd-r1*r2);DSDPCHKERR(info);
    }
  } else {
    info=DSDPVecZero(y);DSDPCHKERR(info);

  }
  DSDPFunctionReturn(0);
}
