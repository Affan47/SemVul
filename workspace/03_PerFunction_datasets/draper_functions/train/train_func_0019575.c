check_cache_control(void){

  char *zETag = cgi_add_etag(zTxt,nUsedTxt);
  char *zMatch = getenv("HTTP_IF_NONE_MATCH");

  if( zETag!=0 && zMatch!=0 ) {
    char *zBuf = strdup(zMatch);
    if( zBuf!=0 ){
      char *zTok = 0;
      char *zPos;
      for( zTok = strtok_r(zBuf, ",\"",&zPos);
           zTok && strcasecmp(zTok,zETag);
           zTok =  strtok_r(0, ",\"",&zPos)){}
      free(zBuf);
      if(zTok) return 1;
    }
  }

  return 0;
}
