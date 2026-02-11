addHighbandEnergies(FIXP_DBL **RESTRICT Energies,
                                    INT       *scaleEnergies,
                                    FIXP_DBL   EnergiesM[NUMBER_TIME_SLOTS_2304][MAX_FREQ_COEFFS],
                                    UCHAR     *RESTRICT freqBandTable,
                                    INT        nSfb,
                                    INT        sbrSlots,
                                    INT        timeStep)
{
  INT i,j,k,slotIn,slotOut,scale;
  INT li,ui;
  FIXP_DBL nrgTotal;
  FIXP_DBL accu = FL2FXCONST_DBL(0.0f);


  for (slotOut=0; slotOut<sbrSlots; slotOut++) {
    slotIn = 2*slotOut;

    for (j=0; j<nSfb; j++) {
      accu = FL2FXCONST_DBL(0.0f);

      li = freqBandTable[j];
      ui = freqBandTable[j + 1];

      for (k=li; k<ui; k++) {
        for (i=0; i<timeStep; i++) {
         accu += (Energies[(slotIn+i)>>1][k] >> 5);
        }
      }
      EnergiesM[slotOut][j] = accu;
    }
  }

  scale = fixMin(8,scaleEnergies[0]);

  if ((scaleEnergies[0]-1) > (DFRACT_BITS-1) )
    nrgTotal = FL2FXCONST_DBL(0.0f);
  else {

    accu = FL2FXCONST_DBL(0.0f);
    for (slotOut=0; slotOut<sbrSlots; slotOut++) {
      for (j=0; j<nSfb; j++) {
        accu += (EnergiesM[slotOut][j] >> scale);
      }
    }
    nrgTotal = accu >> (scaleEnergies[0]-scale);
  }

  return(nrgTotal);
}
