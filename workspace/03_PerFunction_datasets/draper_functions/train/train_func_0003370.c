optionadd(char* b, char* allowed, int c){
  if (strchr(allowed,c) && !strchr(b,c) && strlen(b) < maxoption+1){
    int l = strlen(b);
    b[l]=c; b[l+1]=0;
  }
  return;
}
