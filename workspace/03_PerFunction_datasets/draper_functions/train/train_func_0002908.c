InitPSData(
        HANDLE_PS_DATA            hPsData
        )
{
  FDK_PSENC_ERROR error = PSENC_OK;

  if(hPsData == NULL) {
    error = PSENC_INVALID_HANDLE;
  }
  else {
    int i, env;
    FDKmemclear(hPsData,sizeof(PS_DATA));

    for (i=0; i<PS_MAX_BANDS; i++) {
      hPsData->iidIdxLast[i] = 0;
      hPsData->iccIdxLast[i] = 0;
    }

    hPsData->iidEnable    = hPsData->iidEnableLast = 0;
    hPsData->iccEnable    = hPsData->iccEnableLast = 0;
    hPsData->iidQuantMode = hPsData->iidQuantModeLast = PS_IID_RES_COARSE;
    hPsData->iccQuantMode = hPsData->iccQuantModeLast = PS_ICC_ROT_A;

    for(env=0; env<PS_MAX_ENVELOPES; env++) {
      hPsData->iccDiffMode[env] = PS_DELTA_FREQ;
      hPsData->iccDiffMode[env] = PS_DELTA_FREQ;

      for (i=0; i<PS_MAX_BANDS; i++) {
        hPsData->iidIdx[env][i] = 0;
        hPsData->iccIdx[env][i] = 0;
      }
    }

    hPsData->nEnvelopesLast = 0;

    hPsData->headerCnt  = MAX_PS_NOHEADER_CNT;
    hPsData->iidTimeCnt = MAX_TIME_DIFF_FRAMES;
    hPsData->iccTimeCnt = MAX_TIME_DIFF_FRAMES;
    hPsData->noEnvCnt   = MAX_NOENV_CNT;
  }

  return error;
}
