th_decode_headerin(th_info *_info,th_comment *_tc,
 th_setup_info **_setup,ogg_packet *_op){
  oc_pack_buf opb;
  if(_op==NULL)return TH_EBADHEADER;
  if(_info==NULL)return TH_EFAULT;
  oc_pack_readinit(&opb,_op->packet,_op->bytes);
  return oc_dec_headerin(&opb,_info,_tc,_setup,_op);
}
