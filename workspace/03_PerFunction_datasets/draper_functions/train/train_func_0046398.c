SDPConeSetDenseVecMat(SDPCone sdpcone,int blockj, int vari,int n,
			  double val[], int nnz){
  int info;
  DSDPFunctionBegin;
  info=SDPConeSetADenseVecMat(sdpcone,blockj,vari,n,1.0,val,nnz); DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
