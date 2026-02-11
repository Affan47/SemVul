DSDPLanczosDestroy( DSDPLanczosStepLength *LZ){
  int i,info;
  DSDPFunctionBegin;
  if (LZ->type==2){
    for (i=0;i<=LZ->lanczosm;i++){
      info = SDPConeVecDestroy(&LZ->Q[i]);DSDPCHKERR(info);
    }
    info=SDPConeVecDestroy(&LZ->Tv);DSDPCHKERR(info);
    DSDPFREE(&LZ->darray,&info);DSDPCHKERR(info);
  } else if (LZ->type==1){
    info = SDPConeVecDestroy(&LZ->Q[1]);DSDPCHKERR(info);
    info = SDPConeVecDestroy(&LZ->Q[0]);DSDPCHKERR(info);
    DSDPFREE(&LZ->iwork10n,&info);DSDPCHKERR(info);
  }
  DSDPFREE(&LZ->Q,&info);DSDPCHKERR(info);
  DSDPFREE(&LZ->dwork4n,&info);DSDPCHKERR(info);
  info=DSDPLanczosInitialize(LZ);DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
