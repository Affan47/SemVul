oc_block_run_unpack(oc_pack_buf *_opb){
  long bits;
  long bits2;


  bits=oc_pack_read(_opb,2);
  if((bits&2)==0)return 1+(int)bits;
  else if((bits&1)==0){
    bits=oc_pack_read1(_opb);
    return 3+(int)bits;
  }
  bits=oc_pack_read(_opb,2);
  if((bits&2)==0)return 5+(int)bits;
  else if((bits&1)==0){
    bits=oc_pack_read(_opb,2);
    return 7+(int)bits;
  }
  bits=oc_pack_read(_opb,3);
  if((bits&4)==0)return 11+bits;
  bits2=oc_pack_read(_opb,2);
  return 15+((bits&3)<<2)+bits2;
}
