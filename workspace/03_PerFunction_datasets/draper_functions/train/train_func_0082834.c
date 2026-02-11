getSegmentLowerPos(FXint sg) const {
  register FXdouble shi=seg[nsegs-1].upper;
  register FXdouble slo=seg[0].lower;
  register FXdouble len=shi-slo;
  register FXint pos;
  FXASSERT(0<=sg && sg<nsegs);
  FXASSERT(0<len);
  if(options&GRADIENTBAR_VERTICAL){
    pos=height-padbottom-border-3-(FXint)(0.5+((bar->getHeight()-1)*(seg[sg].lower-slo))/len);
    }
  else{
    pos=padleft+border+2+(FXint)(0.5+((bar->getWidth()-1)*(seg[sg].lower-slo))/len);
    }
  return pos;
  }
