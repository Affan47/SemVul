FDKaacEnc_InitPnsConfiguration(PNS_CONFIG *pnsConf,
                                                 INT         bitRate,
                                                 INT         sampleRate,
                                                 INT         usePns,
                                                 INT         sfbCnt,
                                                 const INT  *sfbOffset,
                                                 const INT   numChan,
                                                 const INT   isLC)
{
  AAC_ENCODER_ERROR ErrorStatus;


  ErrorStatus = FDKaacEnc_GetPnsParam(&pnsConf->np,
                                      bitRate,
                                      sampleRate,
                                      sfbCnt,
                                      sfbOffset,
                                      &usePns,
                                      numChan,
                                      isLC);
  if (ErrorStatus != AAC_ENC_OK)
    return ErrorStatus;

  pnsConf->minCorrelationEnergy = minCorrelationEnergy;
  pnsConf->noiseCorrelationThresh = noiseCorrelationThresh;

  pnsConf->usePns = usePns;

  return AAC_ENC_OK;
}
