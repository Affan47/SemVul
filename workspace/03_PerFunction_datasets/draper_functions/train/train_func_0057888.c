DSDPBlockAddDataMatrix(DSDPBlockData *ADATA,int vari, struct DSDPDataMat_Ops* dsdpdataops, void* data){
  int info,ii;
  DSDPFunctionBegin;
  if (ADATA->nnzmats>=ADATA->maxnnzmats){
    info=DSDPBlockDataAllocate(ADATA,2*ADATA->maxnnzmats+7);DSDPCHKERR(info);
  }
  ii=ADATA->nnzmats;
  info=DSDPDataMatDestroy(&ADATA->A[ii]);DSDPCHKERR(info);
  info=DSDPDataMatSetData(&ADATA->A[ii], dsdpdataops, data);DSDPCHKVARERR(vari,info);
  ADATA->nzmat[ii]=vari;
  ADATA->nnzmats++;
  DSDPFunctionReturn(0);
}
