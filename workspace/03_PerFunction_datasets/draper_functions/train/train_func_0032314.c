transportEnc_LatmCountFixBitDemandHeader ( HANDLE_LATM_STREAM hAss )
{
  int bitDemand = 0;
  int insertSetupData = 0 ;


  if (hAss->subFrameCnt==0)
  {


    if (hAss->tt == TT_MP4_LOAS) {
      bitDemand += 11 ;
      bitDemand += 13 ;
    }


    if (hAss->muxConfigPeriod > 0) {
      insertSetupData = (hAss->latmFrameCounter == 0);
    } else {
      insertSetupData = 0;
    }

    if (hAss->tt != TT_MP4_LATM_MCP0) {

      bitDemand+=1;

      if( insertSetupData ) {
        bitDemand += hAss->streamMuxConfigBits;
      }
    }


    bitDemand += 8*hAss->otherDataLenBytes;


    if ( bitDemand % 8 ) {
       hAss->fillBits = 8 - (bitDemand % 8);
       bitDemand += hAss->fillBits ;
    } else {
      hAss->fillBits = 0;
    }
  }

  return bitDemand ;
}
