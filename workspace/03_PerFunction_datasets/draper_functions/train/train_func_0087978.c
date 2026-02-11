unobscure(const char *zIn){
  int n, i;
  unsigned char salt;
  char *zOut;

  if( zIn==0 ) return 0;
  n = strlen(zIn);
  zOut = fossil_malloc( n + 1 );
  if( n<2
    || decode16((unsigned char*)zIn, &salt, 2)
    || decode16((unsigned char*)&zIn[2], (unsigned char*)zOut, n-2)
  ){
    memcpy(zOut, zIn, n+1);
  }else{
    n = n/2 - 1;
    for(i=0; i<n; i++) zOut[i] = zOut[i]^aObscurer[i&0x0f]^salt;
    zOut[n] = 0;
  }
  return zOut;
}
