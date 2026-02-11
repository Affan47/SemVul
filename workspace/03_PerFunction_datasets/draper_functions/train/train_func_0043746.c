oc_dec_frame_header_unpack(oc_dec_ctx *_dec){
  long val;

  val=oc_pack_read1(&_dec->opb);
  if(val!=0)return TH_EBADPACKET;

  val=oc_pack_read1(&_dec->opb);
  _dec->state.frame_type=(int)val;

  val=oc_pack_read(&_dec->opb,6);
  _dec->state.qis[0]=(unsigned char)val;
  val=oc_pack_read1(&_dec->opb);
  if(!val)_dec->state.nqis=1;
  else{
    val=oc_pack_read(&_dec->opb,6);
    _dec->state.qis[1]=(unsigned char)val;
    val=oc_pack_read1(&_dec->opb);
    if(!val)_dec->state.nqis=2;
    else{
      val=oc_pack_read(&_dec->opb,6);
      _dec->state.qis[2]=(unsigned char)val;
      _dec->state.nqis=3;
    }
  }
  if(_dec->state.frame_type==OC_INTRA_FRAME){


    val=oc_pack_read(&_dec->opb,3);
    if(val!=0)return TH_EIMPL;
  }
  return 0;
}
