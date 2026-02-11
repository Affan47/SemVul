calculateDetectorInput(FIXP_DBL **RESTRICT pQuotaBuffer,
                                   SCHAR     *RESTRICT indexVector,
                                   FIXP_DBL **RESTRICT tonalityDiff,
                                   FIXP_DBL **RESTRICT pSfmOrig,
                                   FIXP_DBL **RESTRICT pSfmSbr,
                                   const UCHAR *freqBandTable,
                                   INT nSfb,
                                   INT noEstPerFrame,
                                   INT move)
{
  INT est;


  for (est=0; est < noEstPerFrame; est++) {

    diff(pQuotaBuffer[est+move],
         tonalityDiff[est+move],
         freqBandTable,
         nSfb,
         indexVector);

    calculateFlatnessMeasure(pQuotaBuffer[est+ move],
                             indexVector,
                             pSfmOrig[est + move],
                             pSfmSbr[est + move],
                             freqBandTable,
                             nSfb);
  }
}
