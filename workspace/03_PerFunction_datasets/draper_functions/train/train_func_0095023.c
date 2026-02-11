FDKaacEnc_CalcNoiseNrgs( const INT    sfbActive,
                           INT         *RESTRICT pnsFlag,
                           FIXP_DBL    *RESTRICT sfbEnergyLdData,
                           INT         *RESTRICT noiseNrg )
{
  int sfb;
  INT tmp = (-LOG_NORM_PCM)<<2;

  for(sfb = 0; sfb < sfbActive; sfb++) {
    if(pnsFlag[sfb]) {
      INT nrg = (-sfbEnergyLdData[sfb]+FL2FXCONST_DBL(0.5f/64.0f))>>(DFRACT_BITS-1-7);
      noiseNrg[sfb] = tmp - nrg;
    }
  }
}
