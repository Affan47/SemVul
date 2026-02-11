oc_comment_unpack(oc_pack_buf *_opb,th_comment *_tc){
  long len;
  int  i;

  len=oc_unpack_length(_opb);
  if(len<0||len>oc_pack_bytes_left(_opb))return TH_EBADHEADER;
  _tc->vendor=_ogg_malloc((size_t)len+1);
  if(_tc->vendor==NULL)return TH_EFAULT;
  oc_unpack_octets(_opb,_tc->vendor,len);
  _tc->vendor[len]='\0';

  _tc->comments=(int)oc_unpack_length(_opb);
  len=_tc->comments;
  if(len<0||len>(LONG_MAX>>2)||len<<2>oc_pack_bytes_left(_opb)){
    _tc->comments=0;
    return TH_EBADHEADER;
  }
  _tc->comment_lengths=(int *)_ogg_malloc(
   _tc->comments*sizeof(_tc->comment_lengths[0]));
  _tc->user_comments=(char **)_ogg_malloc(
   _tc->comments*sizeof(_tc->user_comments[0]));
  for(i=0;i<_tc->comments;i++){
    len=oc_unpack_length(_opb);
    if(len<0||len>oc_pack_bytes_left(_opb)){
      _tc->comments=i;
      return TH_EBADHEADER;
    }
    _tc->comment_lengths[i]=len;
    _tc->user_comments[i]=_ogg_malloc((size_t)len+1);
    if(_tc->user_comments[i]==NULL){
      _tc->comments=i;
      return TH_EFAULT;
    }
    oc_unpack_octets(_opb,_tc->user_comments[i],len);
    _tc->user_comments[i][len]='\0';
  }
  return oc_pack_bytes_left(_opb)<0?TH_EBADHEADER:0;
}
