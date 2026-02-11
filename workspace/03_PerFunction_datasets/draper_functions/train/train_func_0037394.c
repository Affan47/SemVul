encode16(const unsigned char *pIn, unsigned char *zOut, int N){
  int i;
  for(i=0; i<N; i++){
    *(zOut++) = zEncode[pIn[i]>>4];
    *(zOut++) = zEncode[pIn[i]&0xf];
  }
  *zOut = 0;
  return 0;
}
