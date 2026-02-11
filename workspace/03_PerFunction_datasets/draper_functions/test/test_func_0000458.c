adifWrite_EncodeHeader(ADIF_INFO *adif,
                                 HANDLE_FDK_BITSTREAM hBs,
                                 INT adif_buffer_fullness)
{

  const char adifId[5]="ADIF";
  const int  copyRightIdPresent=0;
  const int  originalCopy=0;
  const int  home=0;

  int i;

  INT sampleRate = adif->samplingRate;
  INT totalBitRate = adif->bitRate;

  if (adif->headerWritten)
    return 0;


  UINT alignAnchor = FDKgetValidBits(hBs);


  adif->bVariableRate = ( adif_buffer_fullness >= (INT)(0x1<<20) ) ? 1 : 0;

  FDKwriteBits(hBs, adifId[0],8);
  FDKwriteBits(hBs, adifId[1],8);
  FDKwriteBits(hBs, adifId[2],8);
  FDKwriteBits(hBs, adifId[3],8);


  FDKwriteBits(hBs, copyRightIdPresent ? 1:0,1);

  if(copyRightIdPresent) {
    for(i=0;i<72;i++) {
      FDKwriteBits(hBs,0,1);
    }
  }
  FDKwriteBits(hBs, originalCopy ? 1:0,1);
  FDKwriteBits(hBs, home ? 1:0,1);
  FDKwriteBits(hBs, adif->bVariableRate?1:0, 1);
  FDKwriteBits(hBs, totalBitRate,23);


  FDKwriteBits(hBs, 0, 4);

  if(!adif->bVariableRate) {
    FDKwriteBits(hBs, adif_buffer_fullness, 20);
  }


  transportEnc_writePCE(hBs, adif->cm, sampleRate, adif->instanceTag, adif->profile, 0, 0, alignAnchor);

  return 0;
}
