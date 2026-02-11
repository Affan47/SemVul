FDKaacEnc_resetAHFlags( UCHAR ahFlag[(2)][MAX_GROUPED_SFB],
                          const int nChannels,
                          PSY_OUT_CHANNEL  *psyOutChannel[(2)])
{
  int ch, sfb, sfbGrp;

  for(ch=0; ch<nChannels; ch++) {
    for (sfbGrp=0; sfbGrp < psyOutChannel[ch]->sfbCnt; sfbGrp+=psyOutChannel[ch]->sfbPerGroup) {
      for (sfb=0; sfb<psyOutChannel[ch]->maxSfbPerGroup; sfb++) {
        if ( ahFlag[ch][sfbGrp+sfb] == AH_ACTIVE) {
          ahFlag[ch][sfbGrp+sfb] = AH_INACTIVE;
        }
      }
    }
  }
}
