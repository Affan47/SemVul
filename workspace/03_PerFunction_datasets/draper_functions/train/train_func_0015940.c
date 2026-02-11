DSDPConeTakeDown(SDPCone sdpcone){
  int blockj,info;
  DSDPFunctionBegin;
  for (blockj=0; blockj<sdpcone->nblocks; blockj++){
    info=DSDPBlockTakeDown(&sdpcone->blk[blockj]);DSDPCHKERR(info);
  }
  info=DSDPVecDestroy(&sdpcone->Work);DSDPCHKERR(info);
  info=DSDPVecDestroy(&sdpcone->Work2);DSDPCHKERR(info);
  info=DSDPVecDestroy(&sdpcone->YY);DSDPCHKERR(info);
  info=DSDPVecDestroy(&sdpcone->YX);DSDPCHKERR(info);
  info=DSDPVecDestroy(&sdpcone->DYX);DSDPCHKERR(info);
  info=DSDPDataTransposeTakeDown(&sdpcone->ATR);DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
