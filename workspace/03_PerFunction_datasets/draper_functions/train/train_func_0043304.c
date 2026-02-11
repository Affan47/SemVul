oc_enc_mvs_pack(oc_enc_ctx *_enc){
  const unsigned     *coded_mbis;
  size_t              ncoded_mbis;
  const oc_mb_map    *mb_maps;
  const signed char  *mb_modes;
  const oc_fragment  *frags;
  const oc_mv        *frag_mvs;
  unsigned            mbii;
  int                 mv_scheme;

  mv_scheme=_enc->mv_bits[1]<_enc->mv_bits[0];
  oggpackB_write(&_enc->opb,mv_scheme,1);


  coded_mbis=_enc->coded_mbis;
  ncoded_mbis=_enc->ncoded_mbis;
  mb_modes=_enc->state.mb_modes;
  mb_maps=(const oc_mb_map *)_enc->state.mb_maps;
  frags=_enc->state.frags;
  frag_mvs=(const oc_mv *)_enc->state.frag_mvs;
  for(mbii=0;mbii<ncoded_mbis;mbii++){
    ptrdiff_t fragi;
    unsigned  mbi;
    int       bi;
    mbi=coded_mbis[mbii];
    switch(mb_modes[mbi]){
      case OC_MODE_INTER_MV:
      case OC_MODE_GOLDEN_MV:{
        for(bi=0;;bi++){
          fragi=mb_maps[mbi][0][bi];
          if(frags[fragi].coded){
            oc_enc_mv_pack(_enc,mv_scheme,
             frag_mvs[fragi][0],frag_mvs[fragi][1]);

            break;
          }
        }
      }break;
      case OC_MODE_INTER_MV_FOUR:{
        for(bi=0;bi<4;bi++){
          fragi=mb_maps[mbi][0][bi];
          if(frags[fragi].coded){
            oc_enc_mv_pack(_enc,mv_scheme,
             frag_mvs[fragi][0],frag_mvs[fragi][1]);

          }
        }
      }break;
    }
  }
}
