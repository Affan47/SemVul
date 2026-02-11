utf2mb(FXchar* dst,FXint ndst,const FXchar* src,FXint nsrc) const {
  register FXint nr,nw,len=0;
  FXwchar w;
  if(dst && src && 0<nsrc){
    dst[0]='\xFE';
    dst[1]='\xFF';
    dst+=2;
    len+=2;
    while(0<nsrc){
      nr=utf2wc(w,src,nsrc);
      if(nr<=0) return nr;
      src+=nr;
      nsrc-=nr;
      nw=wc2mb(dst,ndst,w);
      if(nw<=0) return nw;
      len+=nw;
      dst+=nw;
      ndst-=nw;
      }
    }
  return len;
  }
