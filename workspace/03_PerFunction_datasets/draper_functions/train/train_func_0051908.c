onPaint(FXObject*,FXSelector,void* ptr){
  FXEvent *ev=(FXEvent*)ptr;
  FXDCWindow dc(this,ev);
  FXint imgx,imgy,imgw,imgh;
  dc.setForeground(backColor);
  if(image){
    imgw=image->getWidth();
    imgh=image->getHeight();
    if(options&JUSTIFY_LEFT) imgx=padleft+border;
    else if(options&JUSTIFY_RIGHT) imgx=width-padright-border-imgw;
    else imgx=border+padleft+(width-padleft-padright-(border<<1)-imgw)/2;
    if(options&JUSTIFY_TOP) imgy=padtop+border;
    else if(options&JUSTIFY_BOTTOM) imgy=height-padbottom-border-imgh;
    else imgy=border+padtop+(height-padbottom-padtop-(border<<1)-imgh)/2;
    dc.fillRectangle(border,border,imgx-border,height-(border<<1));
    dc.fillRectangle(imgx+imgw,border,width-border-imgx-imgw,height-(border<<1));
    dc.fillRectangle(imgx,border,imgw,imgy-border);
    dc.fillRectangle(imgx,imgy+imgh,imgw,height-border-imgy-imgh);
    dc.drawImage(image,imgx,imgy);
    }
  else{
    dc.fillRectangle(border,border,width-(border<<1),height-(border<<1));
    }
  drawFrame(dc,0,0,width,height);
  return 1;
  }
