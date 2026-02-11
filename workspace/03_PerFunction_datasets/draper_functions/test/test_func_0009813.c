ApplyTools ( CAacDecoderChannelInfo *pAacDecoderChannelInfo[],
                  const SamplingRateInfo *pSamplingRateInfo,
                  const UINT flags,
                  const int channel )
{

  if ( !(flags & (AC_USAC|AC_RSVD50|AC_MPS_RES)) ) {
    CPns_Apply(
           &pAacDecoderChannelInfo[channel]->data.aac.PnsData,
           &pAacDecoderChannelInfo[channel]->icsInfo,
            pAacDecoderChannelInfo[channel]->pSpectralCoefficient,
            pAacDecoderChannelInfo[channel]->specScale,
            pAacDecoderChannelInfo[channel]->pDynData->aScaleFactor,
            pSamplingRateInfo,
            pAacDecoderChannelInfo[channel]->granuleLength,
            channel
            );
  }

  CTns_Apply (
         &pAacDecoderChannelInfo[channel]->pDynData->TnsData,
         &pAacDecoderChannelInfo[channel]->icsInfo,
          pAacDecoderChannelInfo[channel]->pSpectralCoefficient,
          pSamplingRateInfo,
          pAacDecoderChannelInfo[channel]->granuleLength
          );
}
