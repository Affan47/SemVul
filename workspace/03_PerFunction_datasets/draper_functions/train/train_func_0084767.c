est_uconv_out(const char *ptr, int size, int *sp){
  const unsigned char *rp;
  char *rbuf, *wp;
  int c;
  assert(ptr && size >= 0);
  if(size % 2 != 0) size--;
  rp = (unsigned char *)ptr;
  CB_MALLOC(rbuf, size * 2 + 1);
  wp = rbuf;
  while(rp < (unsigned char *)ptr + size){
    c = rp[0] * 0x100 + rp[1];
    if(c < 0x0080){
      *(wp++) = rp[1];
    } else if(c < 0x0900){
      *(wp++) = 0xc0 | (rp[0] << 2) | ((rp[1] >> 6) & 0x03);
      *(wp++) = 0x80 | (rp[1] & 0x3f);
    } else {
      *(wp++) = 0xe0 | ((rp[0] >> 4) & 0x0f);
      *(wp++) = 0x80 | ((rp[0] & 0x0f) << 2) | ((rp[1] >> 6) & 0x03);
      *(wp++) = 0x80 | (rp[1] & 0x3f);
    }
    rp += 2;
  }
  *wp = '\0';
  if(sp) *sp = wp - rbuf;
  return rbuf;
}
