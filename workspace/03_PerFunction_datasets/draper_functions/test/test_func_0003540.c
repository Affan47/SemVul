H(uint64_t tweakey) {

  uint64_t i;
  uint64_t shiftIn;
  uint64_t shiftOut;
  uint64_t res=0;
  for (i=0; i<16; i++) {
    shiftIn=60ULL-4ULL*i;
    shiftOut=60ULL-4ULL*perm[i];
    res^=((tweakey>>shiftIn)&0xf)<<shiftOut;
  }
 return res;
}
