FDKsbrEnc_initPsBandNrgScale(HANDLE_PS_ENCODE hPsEncode)
{
  INT group, bin;
  INT nIidGroups   = hPsEncode->nQmfIidGroups + hPsEncode->nSubQmfIidGroups;

  FDKmemclear(hPsEncode->psBandNrgScale, PS_MAX_BANDS*sizeof(SCHAR));

  for (group=0; group < nIidGroups; group++) {

    bin = hPsEncode->subband2parameterIndex[group];


    if (hPsEncode->psEncMode == PS_BANDS_COARSE) {
      bin = bin>>1;
    }

    hPsEncode->psBandNrgScale[bin] = (hPsEncode->psBandNrgScale[bin]==0)
                          ? (hPsEncode->iidGroupWidthLd[group] + 5)
                          : (fixMax(hPsEncode->iidGroupWidthLd[group],hPsEncode->psBandNrgScale[bin]) + 1) ;

  }
}
