transportDec_ReadAccessUnit( const HANDLE_TRANSPORTDEC hTp, const UINT layer )
{
  TRANSPORTDEC_ERROR err = TRANSPORTDEC_OK;
  HANDLE_FDK_BITSTREAM hBs;

  if (!hTp) {
    return TRANSPORTDEC_INVALID_PARAMETER;
  }

  hBs = &hTp->bitStream[layer];

  switch (hTp->transportFmt) {

    case TT_MP4_ADIF:

      if (!(hTp->flags & TPDEC_CONFIG_FOUND))
      {
        CProgramConfig *pce;

        AudioSpecificConfig_Init(&hTp->asc[0]);
        pce = &hTp->asc[0].m_progrConfigElement;
        err = adifRead_DecodeHeader(&hTp->parser.adif, pce, hBs);
        if (err)
          goto bail;


        hTp->asc[0].m_aot                    = (AUDIO_OBJECT_TYPE)(pce->Profile + 1);
        hTp->asc[0].m_samplingFrequencyIndex = pce->SamplingFrequencyIndex;
        hTp->asc[0].m_samplingFrequency      = SamplingRateTable[pce->SamplingFrequencyIndex];
        hTp->asc[0].m_channelConfiguration   = 0;
        hTp->asc[0].m_samplesPerFrame        = 1024;
        hTp->avgBitRate                      = hTp->parser.adif.BitRate;


        {
          int errC;

          errC = hTp->callbacks.cbUpdateConfig(hTp->callbacks.cbUpdateConfigData, &hTp->asc[0]);
          if (errC == 0) {
            hTp->flags |= TPDEC_CONFIG_FOUND;
          } else {
            err = TRANSPORTDEC_PARSE_ERROR;
            goto bail;
          }
        }
      }
      hTp->auLength[layer] = -1;
      break;

    case TT_MP4_RAW:
      if ((INT)FDKgetValidBits(hBs) <= 0 && layer == 0) {
        err = TRANSPORTDEC_NOT_ENOUGH_BITS;
      }


      hTp->auLength[layer] = FDKgetValidBits(hBs);
      hTp->flags |= TPDEC_SYNCOK;
      break;

    case TT_RSVD50:
    case TT_MP4_ADTS:
    case TT_MP4_LOAS:
    case TT_MP4_LATM_MCP0:
    case TT_MP4_LATM_MCP1:
      err = transportDec_readStream(hTp, layer);
      break;

    default:
      err = TRANSPORTDEC_UNSUPPORTED_FORMAT;
      break;
  }

  if (err == TRANSPORTDEC_OK) {
    hTp->accessUnitAnchor[layer] = FDKgetValidBits(hBs);
  } else {
    hTp->accessUnitAnchor[layer] = 0;
  }

bail:
  return err;
}
