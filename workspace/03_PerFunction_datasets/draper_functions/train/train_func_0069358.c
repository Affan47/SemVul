configure_receive_all(Blob *pIn, int groupMask){
  Blob line;
  int nToken;
  int size;
  Blob aToken[4];

  configHasBeenReset = 0;
  while( blob_line(pIn, &line) ){
    if( blob_buffer(&line)[0]=='#' ) continue;
    nToken = blob_tokenize(&line, aToken, count(aToken));
    if( blob_eq(&aToken[0],"config")
     && nToken==3
     && blob_is_int(&aToken[2], &size)
    ){
      const char *zName = blob_str(&aToken[1]);
      Blob content;
      blob_zero(&content);
      blob_extract(pIn, size, &content);
      g.perm.Admin = g.perm.RdAddr = 1;
      configure_receive(zName, &content, groupMask);
      blob_reset(&content);
      blob_seek(pIn, 1, BLOB_SEEK_CUR);
    }
  }
}
