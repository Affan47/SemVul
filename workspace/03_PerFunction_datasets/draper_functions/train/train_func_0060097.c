transportEnc_writeELDSpecificConfig(
                                         HANDLE_FDK_BITSTREAM hBs,
                                         CODER_CONFIG *config,
                                         int        epConfig,
                                         CSTpCallBacks *cb
                                        )
{

  if (config->channelMode == MODE_1_1) {
    return -1;
  }
  FDKwriteBits(hBs, (config->samplesPerFrame == 480) ? 1 : 0, 1);

  FDKwriteBits(hBs, (config->flags & CC_VCB11 ) ? 1:0, 1);
  FDKwriteBits(hBs, (config->flags & CC_RVLC ) ? 1:0, 1);
  FDKwriteBits(hBs, (config->flags & CC_HCR  ) ? 1:0, 1);

  FDKwriteBits(hBs, (config->flags & CC_SBR) ? 1:0, 1);
  if ( (config->flags & CC_SBR) ) {
    FDKwriteBits(hBs, (config->samplingRate == config->extSamplingRate) ? 0:1, 1);
    FDKwriteBits(hBs, (config->flags & CC_SBRCRC) ? 1:0, 1);

    if (cb->cbSbr != NULL) {
      const PCE_CONFIGURATION *pPce;
      int e;

      pPce = getPceEntry(config->channelMode);

      for (e=0; e<PCE_MAX_ELEMENTS && pPce->el_list[e] != ID_NONE; e++  ) {
        if ( (pPce->el_list[e] == ID_SCE) || (pPce->el_list[e] == ID_CPE) ) {
          cb->cbSbr(cb->cbSbrData, hBs, 0, 0, 0, config->aot, pPce->el_list[e], e);
        }
      }
    }
  }

  FDKwriteBits(hBs, 0, 4);

  return 0;
}
