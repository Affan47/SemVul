DSDPTakeDown(DSDP dsdp){

  int i,info;

  DSDPFunctionBegin;
  DSDPValid(dsdp);
  info = DSDPVecDestroy(&dsdp->rhs);DSDPCHKERR(info);
  info = DSDPVecDestroy(&dsdp->rhs1);DSDPCHKERR(info);
  info = DSDPVecDestroy(&dsdp->rhs2);DSDPCHKERR(info);
  info = DSDPVecDestroy(&dsdp->rhstemp);DSDPCHKERR(info);
  info = DSDPVecDestroy(&dsdp->y);DSDPCHKERR(info);
  info = DSDPVecDestroy(&dsdp->ytemp);DSDPCHKERR(info);
  info = DSDPVecDestroy(&dsdp->dy1);DSDPCHKERR(info);
  info = DSDPVecDestroy(&dsdp->dy2);DSDPCHKERR(info);
  info = DSDPVecDestroy(&dsdp->dy);DSDPCHKERR(info);
  for (i=0;i<MAX_XMAKERS;i++){
    info = DSDPVecDestroy(&dsdp->xmaker[i].y);DSDPCHKERR(info);
    info = DSDPVecDestroy(&dsdp->xmaker[i].dy);DSDPCHKERR(info);
    info = DSDPVecDestroy(&dsdp->xmaker[i].rhs);DSDPCHKERR(info);
  }
  info = DSDPVecDestroy(&dsdp->xmakerrhs);DSDPCHKERR(info);
  info = DSDPVecDestroy(&dsdp->y0);DSDPCHKERR(info);
  info = DSDPVecDestroy(&dsdp->b);DSDPCHKERR(info);

  info = DSDPCGDestroy(&dsdp->sles);DSDPCHKERR(info);
  info = DSDPDestroyCones(dsdp);DSDPCHKERR(info);
  info = DSDPSchurMatDestroy(&dsdp->M);DSDPCHKERR(info);
  info = DSDPGetConicDimension(dsdp,&dsdp->np);DSDPCHKERR(info);
  dsdp->setupcalled=DSDP_FALSE;
  DSDPFunctionReturn(0);
}
