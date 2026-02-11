re_dline_match(
  ReCompiled *pRe,
  DLine *aDLine,
  int N
){
  while( N-- ){
    if( re_match(pRe, (const unsigned char *)aDLine->z, LENGTH(aDLine)) ){
      return 1;
    }
    aDLine++;
  }
  return 0;
}
