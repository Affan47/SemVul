remove_blank_lines(const char *zOrig){
  int i, j, n;
  char *z;
  for(i=j=0; fossil_isspace(zOrig[i]); i++){ if( zOrig[i]=='\n' ) j = i+1; }
  n = strlen(&zOrig[j]);
  while( n>0 && fossil_isspace(zOrig[j+n-1]) ){ n--; }
  z = mprintf("%.*s", n, &zOrig[j]);
  for(i=j=0; z[i]; i++){
    if( z[i+1]=='\n' && z[i]!='\n' && fossil_isspace(z[i]) ){
      z[j] = z[i];
      while(fossil_isspace(z[j]) && z[j] != '\n' ){ j--; }
      j++;
      continue;
    }

    z[j++] = z[i];
  }
  z[j] = 0;
  return z;
}
