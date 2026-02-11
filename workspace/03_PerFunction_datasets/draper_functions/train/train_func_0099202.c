oc_satd16_halfpel(const oc_enc_ctx *_enc,
 const ptrdiff_t *_frag_buf_offs,const ptrdiff_t _fragis[4],
 int _mvoffset0,int _mvoffset1,const unsigned char *_src,
 const unsigned char *_ref,int _ystride,unsigned _best_err){
  unsigned err;
  int      bi;
  err=0;
  for(bi=0;bi<4;bi++){
    ptrdiff_t frag_offs;
    frag_offs=_frag_buf_offs[_fragis[bi]];
    err+=oc_enc_frag_satd2_thresh(_enc,_src+frag_offs,_ref+frag_offs+_mvoffset0,
     _ref+frag_offs+_mvoffset1,_ystride,_best_err-err);
  }
  return err;
}
