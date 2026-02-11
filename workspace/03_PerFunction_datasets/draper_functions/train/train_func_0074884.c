mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const {
  if(nsrc<4) return -4;
#if FOX_BIGENDIAN
  ((FXuchar*)&wc)[0]=src[3];
  ((FXuchar*)&wc)[1]=src[2];
  ((FXuchar*)&wc)[2]=src[1];
  ((FXuchar*)&wc)[3]=src[0];
#else
  ((FXuchar*)&wc)[3]=src[3];
  ((FXuchar*)&wc)[2]=src[2];
  ((FXuchar*)&wc)[1]=src[1];
  ((FXuchar*)&wc)[0]=src[0];
#endif
  return 4;
  }
