cgi_add_etag(char *zTxt, int nLen){
  MD5Context ctx;
  unsigned char digest[16];
  int i, j;
  char zETag[64];

  MD5Init(&ctx);
  MD5Update(&ctx,(unsigned char *)zTxt,(unsigned int)nLen);
  MD5Final(digest,&ctx);
  for(j=i=0; i<16; i++,j+=2){
    bprintf(&zETag[j],sizeof(zETag)-j,"%02x",(int)digest[i]);
  }
  cgi_append_header( mprintf("ETag: %s\r\n", zETag) );
  return strdup(zETag);
}
