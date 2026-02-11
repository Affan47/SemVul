grep(ReCompiled *pRe, const char *zFile, FILE *in){
  int ln = 0;
  int n;
  char zLine[2000];
  while( fgets(zLine, sizeof(zLine), in) ){
    ln++;
    n = (int)strlen(zLine);
    while( n && (zLine[n-1]=='\n' || zLine[n-1]=='\r') ) n--;
    if( re_match(pRe, (const unsigned char*)zLine, n) ){
      printf("%s:%d:%.*s\n", zFile, ln, n, zLine);
    }
  }
}
