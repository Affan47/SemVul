decode16(const unsigned char *zIn, unsigned char *pOut, int N){
  int i, j;
  if( (N&1)!=0 ) return 1;
  for(i=j=0; i<N; i += 2, j++){
    int v1, v2, a;
    a = zIn[i];
    if( (a & 0x80)!=0 || (v1 = zDecode[a])==64 ) return 1;
    a = zIn[i+1];
    if( (a & 0x80)!=0 || (v2 = zDecode[a])==64 ) return 1;
    pOut[j] = (v1<<4) + v2;
  }
  return 0;
}
