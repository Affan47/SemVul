diff_print_filenames(const char *zLeft, const char *zRight, u64 diffFlags){
  char *z = 0;
  if( diffFlags & DIFF_BRIEF ){

  }else if( diffFlags & DIFF_SIDEBYSIDE ){
    int w = diff_width(diffFlags);
    int n1 = strlen(zLeft);
    int x;
    if( n1>w*2 ) n1 = w*2;
    x = w*2+17 - (n1+2);
    z = mprintf("%.*c %.*s %.*c\n",
                x/2, '=', n1, zLeft, (x+1)/2, '=');
  }else{
    z = mprintf("--- %s\n+++ %s\n", zLeft, zRight);
  }
  fossil_print("%s", z);
  fossil_free(z);
}
