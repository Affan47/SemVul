DSDPDataTransposeTakeDown(DSDPDataTranspose *ATranspose){
  int info;
  DSDPFunctionBegin;
  DSDPFREE(&ATranspose->ttnzmat,&info);DSDPCHKERR(info);
  DSDPFREE(&ATranspose->idAP,&info);DSDPCHKERR(info);
  DSDPFREE(&ATranspose->nzblocks,&info);DSDPCHKERR(info);
  DSDPFREE(&ATranspose->nnzblocks,&info);DSDPCHKERR(info);
  DSDPFREE(&ATranspose->idA,&info);DSDPCHKERR(info);
  info=DSDPDataTransposeInitialize(ATranspose);DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
