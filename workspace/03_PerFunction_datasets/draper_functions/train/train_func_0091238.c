oc_enc_rc_2pass_out(oc_enc_ctx *_enc,unsigned char **_buf){
  if(_enc->rc.twopass_buffer_bytes==0){
    if(_enc->rc.twopass==0){
      int qi;

      qi=oc_enc_select_qi(_enc,0,0);
      _enc->state.nqis=1;
      _enc->state.qis[0]=qi;
      _enc->rc.twopass=1;
      _enc->rc.frames_total[0]=_enc->rc.frames_total[1]=
       _enc->rc.frames_total[2]=0;
      _enc->rc.scale_sum[0]=_enc->rc.scale_sum[1]=0;

      oc_rc_buffer_val(&_enc->rc,0x5032544F,4);
      oc_rc_buffer_val(&_enc->rc,OC_RC_2PASS_VERSION,4);
      oc_rc_buffer_val(&_enc->rc,0,OC_RC_2PASS_HDR_SZ-8);
    }
    else{
      int qti;
      qti=_enc->rc.cur_metrics.frame_type;
      _enc->rc.scale_sum[qti]+=oc_bexp_q24(_enc->rc.cur_metrics.log_scale);
      _enc->rc.frames_total[qti]++;
      _enc->rc.frames_total[2]+=_enc->rc.cur_metrics.dup_count;
      oc_rc_buffer_val(&_enc->rc,
       _enc->rc.cur_metrics.dup_count|_enc->rc.cur_metrics.frame_type<<31,4);
      oc_rc_buffer_val(&_enc->rc,_enc->rc.cur_metrics.log_scale,4);
    }
  }
  else if(_enc->packet_state==OC_PACKET_DONE&&
   _enc->rc.twopass_buffer_bytes!=OC_RC_2PASS_HDR_SZ){
    _enc->rc.twopass_buffer_bytes=0;
    oc_rc_buffer_val(&_enc->rc,0x5032544F,4);
    oc_rc_buffer_val(&_enc->rc,OC_RC_2PASS_VERSION,4);
    oc_rc_buffer_val(&_enc->rc,_enc->rc.frames_total[0],4);
    oc_rc_buffer_val(&_enc->rc,_enc->rc.frames_total[1],4);
    oc_rc_buffer_val(&_enc->rc,_enc->rc.frames_total[2],4);
    oc_rc_buffer_val(&_enc->rc,_enc->rc.exp[0],1);
    oc_rc_buffer_val(&_enc->rc,_enc->rc.exp[1],1);
    oc_rc_buffer_val(&_enc->rc,_enc->rc.scale_sum[0],8);
    oc_rc_buffer_val(&_enc->rc,_enc->rc.scale_sum[1],8);
  }
  else{

    *_buf=NULL;
    return 0;
  }
  *_buf=_enc->rc.twopass_buffer;
  return _enc->rc.twopass_buffer_bytes;
}
