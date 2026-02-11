pullContextNix(pullContext *pctx) {
  unsigned int ii;

  if (pctx) {
    for (ii=0; ii<pctx->volNum; ii++) {
      pctx->vol[ii] = pullVolumeNix(pctx->vol[ii]);
    }
    pctx->volNum = 0;
    for (ii=0; ii<=PULL_INFO_MAX; ii++) {
      if (pctx->ispec[ii]) {
        pctx->ispec[ii] = pullInfoSpecNix(pctx->ispec[ii]);
      }
    }
    pctx->energySpecR = pullEnergySpecNix(pctx->energySpecR);
    pctx->energySpecS = pullEnergySpecNix(pctx->energySpecS);
    pctx->energySpecWin = pullEnergySpecNix(pctx->energySpecWin);
#if PULL_HINTER
    nrrdNuke(pctx->nhinter);
#endif

    airFree(pctx);
  }
  return NULL;
}
