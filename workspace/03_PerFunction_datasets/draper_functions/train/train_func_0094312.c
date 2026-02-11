oc_enc_frag_sub_c(ogg_int16_t _diff[64],const unsigned char *_src,
 const unsigned char *_ref,int _ystride){
  int i;
  for(i=0;i<8;i++){
    int j;
    for(j=0;j<8;j++)_diff[i*8+j]=(ogg_int16_t)(_src[j]-_ref[j]);
    _src+=_ystride;
    _ref+=_ystride;
  }
}
