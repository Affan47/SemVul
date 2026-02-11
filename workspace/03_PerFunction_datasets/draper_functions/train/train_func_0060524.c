oc_dec_mb_modes_unpack(oc_dec_ctx *_dec){
  const oc_mb_map     *mb_maps;
  signed char         *mb_modes;
  const oc_fragment   *frags;
  const unsigned char *alphabet;
  unsigned char        scheme0_alphabet[8];
  oc_mode_unpack_func  mode_unpack;
  size_t               nmbs;
  size_t               mbi;
  long                 val;
  int                  mode_scheme;
  val=oc_pack_read(&_dec->opb,3);
  mode_scheme=(int)val;
  if(mode_scheme==0){
    int mi;


    for(mi=0;mi<OC_NMODES;mi++)scheme0_alphabet[mi]=OC_MODE_INTER_NOMV;
    for(mi=0;mi<OC_NMODES;mi++){
      val=oc_pack_read(&_dec->opb,3);
      scheme0_alphabet[val]=OC_MODE_ALPHABETS[6][mi];
    }
    alphabet=scheme0_alphabet;
  }
  else alphabet=OC_MODE_ALPHABETS[mode_scheme-1];
  if(mode_scheme==7)mode_unpack=oc_clc_mode_unpack;
  else mode_unpack=oc_vlc_mode_unpack;
  mb_modes=_dec->state.mb_modes;
  mb_maps=(const oc_mb_map *)_dec->state.mb_maps;
  nmbs=_dec->state.nmbs;
  frags=_dec->state.frags;
  for(mbi=0;mbi<nmbs;mbi++){
    if(mb_modes[mbi]!=OC_MODE_INVALID){
      int bi;

      for(bi=0;bi<4&&!frags[mb_maps[mbi][0][bi]].coded;bi++);

      if(bi<4)mb_modes[mbi]=alphabet[(*mode_unpack)(&_dec->opb)];

      else mb_modes[mbi]=OC_MODE_INTER_NOMV;
    }
  }
}
