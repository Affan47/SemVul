SDPConeAddDataMatrix(SDPCone sdpcone,int blockj, int vari, int n, char format, struct DSDPDataMat_Ops* dsdpdataops, void* data){
  int info;
  DSDPFunctionBegin;
  info=SDPConeCheckI(sdpcone,vari);DSDPCHKERR(info);
  info=SDPConeCheckJ(sdpcone,blockj);DSDPCHKERR(info);
  info=SDPConeCheckN(sdpcone,blockj,n);DSDPCHKERR(info);
  info=SDPConeCheckStorageFormat(sdpcone,blockj,format);DSDPCHKERR(info);
  info=DSDPBlockAddDataMatrix(&sdpcone->blk[blockj].ADATA,vari,dsdpdataops,data);DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
