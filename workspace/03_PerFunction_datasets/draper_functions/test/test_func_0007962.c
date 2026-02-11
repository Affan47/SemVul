FDKaacEnc_QCInit(QC_STATE *hQC,
                                   struct QC_INIT *init)
{
  hQC->maxBitsPerFrame = init->maxBits;
  hQC->minBitsPerFrame = init->minBits;
  hQC->nElements       = init->channelMapping->nElements;
  hQC->bitResTotMax    = init->bitRes;
  hQC->bitResTot       = init->bitRes;
  hQC->maxBitFac       = init->maxBitFac;
  hQC->bitrateMode     = init->bitrateMode;
  hQC->invQuant        = init->invQuant;
  hQC->maxIterations   = init->maxIterations;

  if ( isConstantBitrateMode(hQC->bitrateMode) ) {
    INT bitresPerChannel = (hQC->bitResTotMax / init->channelMapping->nChannelsEff);

    hQC->bitDistributenMode = (bitresPerChannel>50) ? 0 : (bitresPerChannel>0) ? 1 : 2;
  }
  else {
    hQC->bitDistributenMode = 0;
  }


  hQC->padding.paddingRest = init->padding.paddingRest;

  hQC->globHdrBits = init->staticBits;

  FDKaacEnc_InitElementBits(hQC,
                            init->channelMapping,
                            init->bitrate,
                            (init->averageBits/init->nSubFrames) - hQC->globHdrBits,
                            hQC->maxBitsPerFrame/init->channelMapping->nChannelsEff);

  switch(hQC->bitrateMode){
    case QCDATA_BR_MODE_CBR:
    case QCDATA_BR_MODE_VBR_1:
    case QCDATA_BR_MODE_VBR_2:
    case QCDATA_BR_MODE_VBR_3:
    case QCDATA_BR_MODE_VBR_4:
    case QCDATA_BR_MODE_VBR_5:
    case QCDATA_BR_MODE_SFR:
    case QCDATA_BR_MODE_FF:
      if((int)hQC->bitrateMode < (int)(sizeof(tableVbrQualFactor)/sizeof(TAB_VBR_QUAL_FACTOR))){
        hQC->vbrQualFactor = (FIXP_DBL)tableVbrQualFactor[hQC->bitrateMode].vbrQualFactor;
      } else {
        hQC->vbrQualFactor = FL2FXCONST_DBL(0.f);
      }
      break;
    case QCDATA_BR_MODE_INVALID:
    default:
      hQC->vbrQualFactor = FL2FXCONST_DBL(0.f);
      break;
  }

  FDKaacEnc_AdjThrInit(hQC->hAdjThr,
             init->meanPe,
             hQC->elementBits,
             init->channelMapping->nElements,
             hQC->vbrQualFactor);

  return AAC_ENC_OK;
}
