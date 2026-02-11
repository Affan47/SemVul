FDKaacEnc_improveScf(FIXP_DBL *spec,
                      SHORT *quantSpec,
                      SHORT *quantSpecTmp,
                      INT sfbWidth,
                      FIXP_DBL  threshLdData,
                      INT scf,
                      INT minScf,
                      FIXP_DBL  *distLdData,
                      INT *minScfCalculated
                      )
{
   FIXP_DBL sfbDistLdData;
   INT scfBest = scf;
   INT k;
   FIXP_DBL distFactorLdData = FL2FXCONST_DBL(-0.0050301265);


   sfbDistLdData = FDKaacEnc_calcSfbDist(spec,
                                         quantSpec,
                                         sfbWidth,
                                         scf);
   *minScfCalculated = scf;

   if (sfbDistLdData > (threshLdData-distFactorLdData)) {
      INT scfEstimated = scf;
      FIXP_DBL sfbDistBestLdData = sfbDistLdData;
      INT cnt;

      cnt = 0;

      while ((sfbDistLdData > (threshLdData-distFactorLdData)) && (cnt++ < 3)) {
         scf++;
         sfbDistLdData = FDKaacEnc_calcSfbDist(spec,
                                               quantSpecTmp,
                                               sfbWidth,
                                               scf);

         if (sfbDistLdData < sfbDistBestLdData) {
            scfBest = scf;
            sfbDistBestLdData = sfbDistLdData;
            for (k=0; k<sfbWidth; k++)
	             quantSpec[k] = quantSpecTmp[k];
         }
      }

      cnt = 0;
      scf = scfEstimated;
      sfbDistLdData = sfbDistBestLdData;
      while ((sfbDistLdData > (threshLdData-distFactorLdData)) && (cnt++ < 1) && (scf > minScf)) {
         scf--;
         sfbDistLdData = FDKaacEnc_calcSfbDist(spec,
                                               quantSpecTmp,
                                               sfbWidth,
                                               scf);

         if (sfbDistLdData < sfbDistBestLdData) {
            scfBest = scf;
            sfbDistBestLdData = sfbDistLdData;
            for (k=0; k<sfbWidth; k++)
	             quantSpec[k] = quantSpecTmp[k];
         }
         *minScfCalculated = scf;
      }
      *distLdData = sfbDistBestLdData;
   }
   else {
      FIXP_DBL sfbDistBestLdData = sfbDistLdData;
      FIXP_DBL sfbDistAllowedLdData = fixMin(sfbDistLdData-distFactorLdData,threshLdData);
      int cnt;
      for (cnt=0; cnt<3; cnt++) {
         scf++;
         sfbDistLdData = FDKaacEnc_calcSfbDist(spec,
                                               quantSpecTmp,
                                               sfbWidth,
                                               scf);

         if (sfbDistLdData < sfbDistAllowedLdData) {
           *minScfCalculated = scfBest+1;
           scfBest = scf;
           sfbDistBestLdData = sfbDistLdData;
           for (k=0; k<sfbWidth; k++)
             quantSpec[k] = quantSpecTmp[k];
         }
      }
      *distLdData = sfbDistBestLdData;
   }


   return scfBest;
}
