sbrDecoder_Header (
        HANDLE_SBRDECODER       self,
        HANDLE_FDK_BITSTREAM    hBs,
        const INT sampleRateIn,
        const INT sampleRateOut,
        const INT samplesPerFrame,
        const AUDIO_OBJECT_TYPE coreCodec,
        const MP4_ELEMENT_ID    elementID,
        const INT               elementIndex
        )
{
  SBR_HEADER_STATUS headerStatus;
  HANDLE_SBR_HEADER_DATA hSbrHeader;
  SBR_ERROR sbrError = SBRDEC_OK;
  int headerIndex;

  if ( self == NULL || elementIndex > (4) )
  {
    return SBRDEC_UNSUPPORTED_CONFIG;
  }

  if (! sbrDecoder_isCoreCodecValid(coreCodec)) {
    return SBRDEC_UNSUPPORTED_CONFIG;
  }

  sbrError = sbrDecoder_InitElement(
          self,
          sampleRateIn,
          sampleRateOut,
          samplesPerFrame,
          coreCodec,
          elementID,
          elementIndex
          );

  if (sbrError != SBRDEC_OK) {
    goto bail;
  }

  headerIndex = getHeaderSlot(self->pSbrElement[elementIndex]->useFrameSlot,
                              self->pSbrElement[elementIndex]->useHeaderSlot);
  hSbrHeader = &(self->sbrHeader[elementIndex][headerIndex]);

  headerStatus = sbrGetHeaderData ( hSbrHeader,
                                    hBs,
                                    self->flags,
                                    0);


  {
    SBR_DECODER_ELEMENT *pSbrElement;

    pSbrElement = self->pSbrElement[elementIndex];


    if (pSbrElement != NULL) {
      if ( (elementID == ID_CPE && pSbrElement->nChannels != 2)
        || (elementID != ID_CPE && pSbrElement->nChannels != 1) )
      {
        return SBRDEC_UNSUPPORTED_CONFIG;
      }
      if ( headerStatus == HEADER_RESET ) {

        sbrError = sbrDecoder_HeaderUpdate(
              self,
              hSbrHeader,
              headerStatus,
              pSbrElement->pSbrChannel,
              pSbrElement->nChannels
              );

        if (sbrError == SBRDEC_OK) {
          hSbrHeader->syncState = SBR_HEADER;
          hSbrHeader->status   |= SBRDEC_HDR_STAT_UPDATE;
        }


      }
    }
  }
bail:
  return sbrError;
}
