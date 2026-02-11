pcmDmx_ReadDvbAncData (
    HANDLE_PCM_DOWNMIX  self,
    UCHAR *pAncDataBuf,
    UINT   ancDataBytes,
    int    isMpeg2
  )
{
  DVB_MIXDOWN_LEVELS *pDownmixLevels = &self->dvbMixDownLevels[0];

  int   offset = (isMpeg2) ? 2 : 0;
  UCHAR ancDataStatus;

  if (self == NULL) { return (PCMDMX_INVALID_HANDLE); }


  if (pAncDataBuf == NULL || ancDataBytes < (UCHAR)(3+offset)) {
    return (PCMDMX_CORRUPT_ANC_DATA);
  }


  if (pAncDataBuf[offset] != ANC_DATA_SYNC_BYTE) {
    return (PCMDMX_CORRUPT_ANC_DATA);
  }

  offset += 2;
  ancDataStatus = pAncDataBuf[offset++];

  if (isMpeg2) {

    if (ancDataStatus & 0x80) offset += 3;

    if (ancDataStatus & 0x40) offset += 1;

    if (ancDataStatus & 0x20) offset += 1;
  }
  else {

    if (ancDataStatus & 0xE8) { return (PCMDMX_CORRUPT_ANC_DATA); }
  }


  if (ancDataStatus & 0x10)
  {
    int   foundNewData = 0;
    UCHAR downmixData = pAncDataBuf[offset++];

    if (downmixData & 0x80) {
      pDownmixLevels->centerMixLevelValue =
        dvbDownmixFactors[(downmixData >> 4) & 0x07];
      foundNewData = 1;
    } else {
      pDownmixLevels->centerMixLevelValue = dvbDownmixFactors[0];
      if (downmixData & 0x70) { return (PCMDMX_CORRUPT_ANC_DATA); }
    }

    if (downmixData & 0x08) {
      pDownmixLevels->surroundMixLevelValue =
        dvbDownmixFactors[downmixData & 0x07];
      foundNewData = 1;
    } else {
      pDownmixLevels->surroundMixLevelValue = dvbDownmixFactors[0];
      if (downmixData & 0x07) { return (PCMDMX_CORRUPT_ANC_DATA); }
    }

    pDownmixLevels->mixLevelsAvail = foundNewData;
  }


  self->expiryCount = 0;

  return (PCMDMX_OK);
}
