utf2wcs(FXwchar *dst,const FXchar *src,FXint n){
  register FXint len=0;
  register FXint p=0;
  register FXwchar w;
  while(p<n){
    w=(FXuchar)src[p++];
    if(0xC0<=w){ w=(w<<6)^(FXuchar)src[p++]^0x3080;
    if(0x800<=w){ w=(w<<6)^(FXuchar)src[p++]^0x20080;
    if(0x10000<=w){ w=(w<<6)^(FXuchar)src[p++]^0x400080;
    if(0x200000<=w){ w=(w<<6)^(FXuchar)src[p++]^0x8000080;
    if(0x4000000<=w){ w=(w<<6)^(FXuchar)src[p++]^0x80; }}}}}
    dst[len++]=w;
    }
  return len;
  }
