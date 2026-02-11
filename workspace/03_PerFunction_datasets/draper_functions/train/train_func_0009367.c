FDKaacEnc_PreProcessPnsChannelPair(const INT   sfbActive,
                                        FIXP_DBL   *RESTRICT sfbEnergyLeft,
                                        FIXP_DBL   *RESTRICT sfbEnergyRight,
                                        FIXP_DBL   *RESTRICT sfbEnergyLeftLD,
                                        FIXP_DBL   *RESTRICT sfbEnergyRightLD,
                                        FIXP_DBL   *RESTRICT sfbEnergyMid,
                                        PNS_CONFIG *RESTRICT pnsConf,
                                        PNS_DATA   *pnsDataLeft,
                                        PNS_DATA   *pnsDataRight)
{
  INT sfb;
  FIXP_DBL ccf;

  if(!pnsConf->usePns)
    return;

  FIXP_DBL *RESTRICT pNoiseEnergyCorrelationL = pnsDataLeft->noiseEnergyCorrelation;
  FIXP_DBL *RESTRICT pNoiseEnergyCorrelationR = pnsDataRight->noiseEnergyCorrelation;

  for(sfb=0;sfb< sfbActive;sfb++) {
    FIXP_DBL quot = (sfbEnergyLeftLD[sfb]>>1) + (sfbEnergyRightLD[sfb]>>1);

    if(quot < FL2FXCONST_DBL(-32.0f/(float)LD_DATA_SCALING))
      ccf = FL2FXCONST_DBL(0.0f);
    else {
      FIXP_DBL accu = sfbEnergyMid[sfb]- (((sfbEnergyLeft[sfb]>>1)+(sfbEnergyRight[sfb]>>1))>>1);
      INT sign = (accu < FL2FXCONST_DBL(0.0f)) ? 1 : 0 ;
      accu = fixp_abs(accu);

      ccf = CalcLdData(accu) + FL2FXCONST_DBL((float)1.0f/(float)LD_DATA_SCALING) - quot;
      ccf = (ccf>=FL2FXCONST_DBL(0.0)) ? ((FIXP_DBL)MAXVAL_DBL) : (sign) ? -CalcInvLdData(ccf) : CalcInvLdData(ccf);
    }

    pNoiseEnergyCorrelationL[sfb] = ccf;
    pNoiseEnergyCorrelationR[sfb] = ccf;
  }
}
