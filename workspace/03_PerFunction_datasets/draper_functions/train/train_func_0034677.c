oggpackB_look(oggpack_buffer *b,int bits){
  unsigned long ret;
  int m=32-bits;

  if(m<0 || m>32) return -1;
  bits+=b->endbit;

  if(b->endbyte >= b->storage-4){

    if(b->endbyte > b->storage-((bits+7)>>3)) return -1;


    else if(!bits)return(0L);
  }

  ret=b->ptr[0]<<(24+b->endbit);
  if(bits>8){
    ret|=b->ptr[1]<<(16+b->endbit);
    if(bits>16){
      ret|=b->ptr[2]<<(8+b->endbit);
      if(bits>24){
        ret|=b->ptr[3]<<(b->endbit);
        if(bits>32 && b->endbit)
          ret|=b->ptr[4]>>(8-b->endbit);
      }
    }
  }
  return ((ret&0xffffffff)>>(m>>1))>>((m+1)>>1);
}
