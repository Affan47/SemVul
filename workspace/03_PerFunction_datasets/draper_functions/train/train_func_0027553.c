writeSyntheticCodingData (HANDLE_SBR_ENV_DATA  sbrEnvData,
                                     HANDLE_FDK_BITSTREAM hBitStream)

{
  INT i;
  INT payloadBits = 0;

  payloadBits += FDKwriteBits (hBitStream, sbrEnvData->addHarmonicFlag, 1);

  if (sbrEnvData->addHarmonicFlag) {
    for (i = 0; i < sbrEnvData->noHarmonics; i++) {
      payloadBits += FDKwriteBits (hBitStream, sbrEnvData->addHarmonic[i], 1);
    }
  }

  return payloadBits;
}
