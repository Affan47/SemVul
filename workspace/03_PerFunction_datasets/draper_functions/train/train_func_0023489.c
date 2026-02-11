ncslen(const FXchar *str,FXint n){
  register FXint len=0;
  register FXint p=0;
  register FXwchar c;
  while(p<n){
    c=(FXuchar)str[p++];
    if(0xC0<=c){ p++;
    if(0xE0<=c){ p++;
    if(0xF0<=c){ p++;
    if(0xF8<=c){ p++;
    if(0xFC<=c){ p++; }} len++; }}}
    len++;
    }
  return len;
  }
