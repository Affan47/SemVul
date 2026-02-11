cgi_extract_content(int *pnAmt){
  char *z;
  *pnAmt = nUsedTxt;
  if( zTxt ){
    zTxt[nUsedTxt] = 0;
  }
  z = zTxt;
  zTxt = 0;
  nAllocTxt = 0;
  nUsedTxt = 0;
  return z;
}
