CLatmDemux_Read(
        HANDLE_FDK_BITSTREAM bs,
        CLatmDemux *pLatmDemux,
        TRANSPORT_TYPE tt,
        CSTpCallBacks *pTpDecCallbacks,
        CSAudioSpecificConfig *pAsc,
        const INT ignoreBufferFullness
        )
{
  UINT cntBits;
  UINT cmpBufferFullness;
  UINT audioMuxLengthBytesLast = 0;
  TRANSPORTDEC_ERROR ErrorStatus = TRANSPORTDEC_OK;

  cntBits = FDKgetValidBits(bs);

  if ((INT)cntBits < MIN_LATM_HEADERLENGTH) {
    return TRANSPORTDEC_NOT_ENOUGH_BITS;
  }

  if ((ErrorStatus = CLatmDemux_ReadAudioMuxElement(bs, pLatmDemux, (tt != TT_MP4_LATM_MCP0), pTpDecCallbacks, pAsc)))
    return (ErrorStatus);

  if (!ignoreBufferFullness)
  {
    cmpBufferFullness =   24+audioMuxLengthBytesLast*8
                        + pLatmDemux->m_linfo[0][0].m_bufferFullness* pAsc[TPDEC_TRACKINDEX(0,0)].m_channelConfiguration*32;


    if (pLatmDemux->m_linfo[0][0].m_bufferFullness != 0xFF)
    {
      if (!pLatmDemux->BufferFullnessAchieved)
      {
        if (cntBits < cmpBufferFullness)
        {


          return TRANSPORTDEC_NOT_ENOUGH_BITS;
        }
        else
        {
          pLatmDemux->BufferFullnessAchieved = 1;
        }
      }
    }
  }

  return (ErrorStatus);
}
