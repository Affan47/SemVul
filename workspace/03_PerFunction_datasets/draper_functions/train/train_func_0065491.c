oc_mode_scheme_chooser_update(oc_mode_scheme_chooser *_chooser,
 int _mb_mode){
  int ri;
  int si;
  _chooser->mode_counts[_mb_mode]++;

  for(ri=_chooser->scheme0_ranks[_mb_mode];ri>0;ri--){
    int pmode;
    pmode=_chooser->scheme0_list[ri-1];
    if(_chooser->mode_counts[pmode]>=_chooser->mode_counts[_mb_mode])break;

    _chooser->scheme0_ranks[pmode]++;
    _chooser->scheme0_list[ri]=pmode;
  }
  _chooser->scheme0_ranks[_mb_mode]=ri;
  _chooser->scheme0_list[ri]=_mb_mode;

  for(si=0;si<8;si++){
    _chooser->scheme_bits[si]+=
     OC_MODE_BITS[si+1>>3][_chooser->mode_ranks[si][_mb_mode]];
  }

  for(si=1;si<8;si++){
    int sj;
    int scheme0;
    int bits0;
    sj=si;
    scheme0=_chooser->scheme_list[si];
    bits0=_chooser->scheme_bits[scheme0];
    do{
      int scheme1;
      scheme1=_chooser->scheme_list[sj-1];
      if(bits0>=_chooser->scheme_bits[scheme1])break;
      _chooser->scheme_list[sj]=scheme1;
    }
    while(--sj>0);
    _chooser->scheme_list[sj]=scheme0;
  }
}
