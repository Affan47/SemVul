dequote_git_filename(char *zName){
  int n, i, j;
  if( zName==0 || zName[0]!='"' ) return;
  n = (int)strlen(zName);
  if( zName[n-1]!='"' ) return;
  for(i=0, j=1; j<n-1; j++){
    char c = zName[j];
    if( c=='\\' ) c = zName[++j];
    zName[i++] = c;
  }
  zName[i] = 0;
}
