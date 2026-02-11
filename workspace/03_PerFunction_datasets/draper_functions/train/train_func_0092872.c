oc_fr_state_advance_block(oc_fr_state *_fr,int _b_coded){
  ptrdiff_t bits;
  int       b_coded_count;
  int       b_count;
  int       sb_partial;
  int       sb_full=sb_full;
  bits=_fr->bits;

  b_coded_count=_fr->b_coded_count;
  if(_fr->b_coded==_b_coded)bits-=oc_block_run_bits(b_coded_count);
  else b_coded_count=0;
  b_coded_count++;
  b_count=_fr->b_count+1;
  if(b_count>=16){

    if(b_coded_count>=16){

      if(b_coded_count>16)bits+=oc_block_run_bits(b_coded_count-16);
      sb_partial=0;
      sb_full=_b_coded;
      _b_coded=_fr->b_coded_prev;
      b_coded_count=_fr->b_coded_count_prev;
    }
    else{
      bits+=oc_block_run_bits(b_coded_count);

      sb_partial=1;

    }
    _fr->bits=bits;
    _fr->b_coded_count=b_coded_count;
    _fr->b_coded_count_prev=b_coded_count;
    _fr->b_count=0;
    _fr->b_coded=_b_coded;
    _fr->b_coded_prev=_b_coded;
    oc_fr_state_advance_sb(_fr,sb_partial,sb_full);
  }
  else{
    bits+=oc_block_run_bits(b_coded_count);
    _fr->bits=bits;
    _fr->b_coded_count=b_coded_count;
    _fr->b_count=b_count;
    _fr->b_coded=_b_coded;
  }
}
