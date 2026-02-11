operator=(const FXRegion& r){
#ifndef WIN32
  if(region!=r.region){
    XDestroyRegion((Region)region);
    region=XCreateRegion();
    XUnionRegion((Region)r.region,(Region)region,(Region)region);
    }
#else
  CombineRgn((HRGN)region,(HRGN)r.region,(HRGN)r.region,RGN_COPY);
#endif
  return *this;
  }
