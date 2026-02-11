base64_decode(char* buf, size_t bufsiz)
{
  size_t i, j;
  uint8_t *dst = (uint8_t*)buf;

  for(i=0, j=0; i<bufsiz; i+=4, j+=3){
    const int n = _decode_mchar(dst+j, buf+i);
    if(n<3){
      j+=n;
      break;
    }
  }

  return j;
}
