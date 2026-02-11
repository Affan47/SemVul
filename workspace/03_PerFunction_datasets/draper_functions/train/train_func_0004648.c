onPaint(FXObject*,FXSelector,void *ptr){
  FXEvent *event=(FXEvent*)ptr;
  FXDCWindow dc(this,event);


  drawFrame(dc,0,0,width,height);


  dc.setForeground(getBaseColor());
  dc.fillRectangle(border,border,width-(border<<1),height-(border<<1));


  drawInterior(dc);
  return 1;
  }
