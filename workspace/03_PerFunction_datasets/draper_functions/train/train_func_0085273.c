md5sum_file(const char *zFilename, Blob *pCksum){
  FILE *in;
  MD5Context ctx;
  unsigned char zResult[16];
  char zBuf[10240];

  in = fossil_fopen(zFilename,"rb");
  if( in==0 ){
    return 1;
  }
  MD5Init(&ctx);
  for(;;){
    int n;
    n = fread(zBuf, 1, sizeof(zBuf), in);
    if( n<=0 ) break;
    MD5Update(&ctx, (unsigned char*)zBuf, (unsigned)n);
  }
  fclose(in);
  blob_zero(pCksum);
  blob_resize(pCksum, 32);
  MD5Final(zResult, &ctx);
  DigestToBase16(zResult, blob_buffer(pCksum));
  return 0;
}
