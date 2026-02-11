FDKsbrEnc_CreateTonCorrParamExtr(HANDLE_SBR_TON_CORR_EST hTonCorr,
                                 INT                     chan)
{
  INT i;
  FIXP_DBL* quotaMatrix = GetRam_Sbr_quotaMatrix(chan);
  INT*      signMatrix  = GetRam_Sbr_signMatrix(chan);

  FDKmemclear(hTonCorr, sizeof(SBR_TON_CORR_EST));

  for (i=0; i<MAX_NO_OF_ESTIMATES; i++) {
    hTonCorr->quotaMatrix[i] = quotaMatrix + (i*QMF_CHANNELS);
    hTonCorr->signMatrix[i]  = signMatrix  + (i*QMF_CHANNELS);
  }

  FDKsbrEnc_CreateSbrMissingHarmonicsDetector (&hTonCorr->sbrMissingHarmonicsDetector, chan);

  return 0;
}
