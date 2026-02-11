DSDPVMatCheck(DSDPVMat X, SDPConeVec W1, SDPConeVec W2){
  int info,i,n,nn;
  double *xx,eig,eps=1e-13,one=1.0;
  double fnorm0,fnorm1,fnorm2,fnorm3,fnorm4;
  DSDPFunctionBegin;
  info=DSDPVMatGetSize(X,&n);DSDPCHKERR(info);
  info=SDPConeVecSet(one,W1);DSDPCHKERR(info);
  info=DSDPVMatAddOuterProduct(X,1.23456,W1);DSDPCHKERR(info);
  info=DSDPVMatZeroEntries(X);DSDPCHKERR(info);
  info=DSDPVMatNormF2(X,&fnorm0);DSDPCHKERR(info);
  if (fabs(fnorm0)>eps){ printf("Check DSDPVMatZero of DSDPVMatNorm\n");}

  info=SDPConeVecSet(one,W1);DSDPCHKERR(info);
  info=DSDPVMatAddOuterProduct(X,1.0,W1);DSDPCHKERR(info);
  info=DSDPVMatNormF2(X,&fnorm1);DSDPCHKERR(info);
  if (fabs(fnorm1-n*n)>eps) printf("Check DSDPVMatZero()\n");

  info=DSDPVMatGetArray(X,&xx,&nn);DSDPCHKERR(info);
  for (i=0;i<nn;i++){xx[i]=1.0;}
  info=DSDPVMatRestoreArray(X,&xx,&nn);DSDPCHKERR(info);
  info=DSDPVMatNormF2(X,&fnorm2);DSDPCHKERR(info);
  if (fabs(fnorm2-n*n)>eps) printf("Check DSDPXGetArray()\n");

  info=DSDPVMatAddOuterProduct(X,-1.0,W1);DSDPCHKERR(info);
  info=DSDPVMatNormF2(X,&fnorm3);DSDPCHKERR(info);

  info=DSDPVMatZeroEntries(X);DSDPCHKERR(info);
  info=DSDPVMatAddOuterProduct(X,1.0,W1);DSDPCHKERR(info);
  info=DSDPVMatScaleDiagonal(X,2.0);DSDPCHKERR(info);

  info=DSDPVMatZeroEntries(X);DSDPCHKERR(info);
  info=DSDPVMatAddOuterProduct(X,1.0,W1);DSDPCHKERR(info);
  info=DSDPVMatShiftDiagonal(X,1.0);DSDPCHKERR(info);
  info=DSDPVMatNormF2(X,&fnorm4);DSDPCHKERR(info);

  info=DSDPVMatMult(X,W1,W2);DSDPCHKERR(info);
  info=DSDPVMatMinEigenvalue(X,W1,W2,&eig);DSDPCHKERR(info);
  if (fabs(fnorm0)>eps) printf("Check DSDPVMatZero()\n");
  DSDPFunctionReturn(0);
}
