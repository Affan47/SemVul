onPaint(FXObject*,FXSelector,void* ptr){
  FXEvent* event=static_cast<FXEvent*>(ptr);
  FXDCWindow dc(this,event);
  FXint tw,th,tx,ty;
  dc.setForeground(backColor);
  dc.fillRectangle(border,border,width-(border<<1),height-(border<<1));
  if(!caption.empty()){
    dc.setFont(font);
    tw=font->getTextWidth(caption.text(),caption.length());
    th=font->getFontHeight();
    if(options&JUSTIFY_LEFT) tx=padleft+border;
    else if(options&JUSTIFY_RIGHT) tx=width-padright-border-tw;
    else tx=border+padleft+(width-padleft-padright-(border<<1)-tw)/2;
    if(options&JUSTIFY_TOP) ty=border+padtop;
    else if(options&JUSTIFY_BOTTOM) ty=height-padbottom-border-th;
    else ty=border+padtop+(height-padbottom-padtop-(border<<1)-th)/2;
    dc.setForeground(captionColor);
    dc.drawText(tx,ty+font->getFontAscent(),caption);
    }
  drawFrame(dc,0,0,width,height);
  return 1;
  }
