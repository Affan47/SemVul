oc_analyze_mb_mode_chroma(oc_enc_ctx *_enc,
 oc_mode_choice *_modec,const oc_fr_state *_fr,const oc_qii_state *_qs,
 const unsigned _frag_satd[12],const unsigned _skip_ssd[12],int _qti){
  unsigned ssd;
  unsigned rate;
  unsigned satd;
  unsigned best_ssd;
  unsigned best_rate;
  int      best_qii;
  unsigned cur_cost;
  unsigned cur_ssd;
  unsigned cur_rate;
  int      lambda;
  int      nblocks;
  int      nqis;
  int      pli;
  int      bi;
  int      qii;
  lambda=_enc->lambda;
  nqis=_enc->state.nqis;
  ssd=_modec->ssd;
  rate=_modec->rate;


  nblocks=OC_MB_MAP_NIDXS[_enc->state.info.pixel_fmt];
  nblocks=(nblocks-4>>1)+4;
  bi=4;
  for(pli=1;pli<3;pli++){
    for(;bi<nblocks;bi++){
      unsigned best_cost;
      satd=_frag_satd[bi];
      best_rate=oc_dct_cost2(&best_ssd,_enc->state.qis[0],pli,_qti,satd)
       +OC_CHROMA_QII_RATE;
      best_cost=OC_MODE_RD_COST(ssd+best_ssd,rate+best_rate,lambda);
      best_qii=0;
      for(qii=1;qii<nqis;qii++){
        cur_rate=oc_dct_cost2(&cur_ssd,_enc->state.qis[qii],0,_qti,satd)
         +OC_CHROMA_QII_RATE;
        cur_cost=OC_MODE_RD_COST(ssd+cur_ssd,rate+cur_rate,lambda);
        if(cur_cost<best_cost){
          best_cost=cur_cost;
          best_ssd=cur_ssd;
          best_rate=cur_rate;
          best_qii=qii;
        }
      }
      if(_skip_ssd[bi]<UINT_MAX){
        cur_ssd=_skip_ssd[bi]<<OC_BIT_SCALE;
        cur_cost=OC_MODE_RD_COST(ssd+cur_ssd,rate,lambda);
        if(cur_cost<=best_cost){
          best_ssd=cur_ssd;
          best_rate=0;
          best_qii+=4;
        }
      }
      rate+=best_rate;
      ssd+=best_ssd;
      _modec->qii[bi]=best_qii;
    }
    nblocks=(nblocks-4<<1)+4;
  }
  _modec->ssd=ssd;
  _modec->rate=rate;
}
