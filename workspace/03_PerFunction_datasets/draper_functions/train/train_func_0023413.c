LPComputeATY(LPCone lpcone,DSDPVec Y, DSDPVec S){
  int info,m=lpcone->m,n=lpcone->n;
  double cc,r,*s,*y;
  DSDPVec C=lpcone->C;
  smatx *A=lpcone->A;
  DSDPFunctionBegin;
  if (lpcone->n<1) return 0;
  info=DSDPVecGetC(Y,&cc);DSDPCHKERR(info);
  info=DSDPVecGetR(Y,&r);DSDPCHKERR(info);
  info=DSDPVecGetSize(S,&n);DSDPCHKERR(info);
  info=DSDPVecGetArray(S,&s);DSDPCHKERR(info);
  info=DSDPVecGetArray(Y,&y);DSDPCHKERR(info);
  info=SpRowMatMultTrans(A,y+1,m,s,n); DSDPCHKERR(info);
  info=DSDPVecRestoreArray(S,&s);DSDPCHKERR(info);
  info=DSDPVecRestoreArray(Y,&y);DSDPCHKERR(info);
  info=DSDPVecAXPY(cc,C,S);DSDPCHKERR(info);
  info=DSDPVecShift(r*lpcone->r,S);DSDPCHKERR(info);
  info=DSDPVecScale(-1.0,S);DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
