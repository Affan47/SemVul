mult_calc(byte a, byte b) {
  byte p = 0;
  unsigned char to_reduce, i;
  for(i = 0; i < 8; i++) {
    if(b & 1) {
      p ^= a;
    }
    to_reduce = a & 0x80;
    a <<= 1;
    if(to_reduce)
      a ^= 0x1b;
    b >>= 1;
  }
  return p;
}
