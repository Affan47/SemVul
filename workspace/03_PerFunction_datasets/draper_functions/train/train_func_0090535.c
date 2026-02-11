drawHSplit(FXint pos){
  FXDCWindow dc(this);
  dc.clipChildren(FALSE);
  dc.setFunction(BLT_NOT_DST);
  dc.fillRectangle(pos,0,barsize,height);
  }
