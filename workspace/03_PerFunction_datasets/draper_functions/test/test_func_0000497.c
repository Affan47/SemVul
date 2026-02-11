onPaint(FXObject*,FXSelector,void* ptr){
  FXint tw=0,th=0,iw=MENUGLYPH_WIDTH,ih=MENUGLYPH_HEIGHT,tx,ty,ix,iy;
  FXEvent *ev=(FXEvent*)ptr;
  FXDCWindow dc(this,ev);

  drawFrame(dc,0,0,width,height);


  dc.setForeground(backColor);
  dc.fillRectangle(border,border,width-border*2,height-border*2);


  if(!label.empty()){
    tw=labelWidth(label);
    th=labelHeight(label);
    }
  if(icon){
    iw=icon->getWidth();
    ih=icon->getHeight();
    }

  just_x(tx,ix,tw,iw);
  just_y(ty,iy,th,ih);


  if(isEnabled()){
    if(icon){
      dc.drawIcon(icon,ix,iy);
      }
    else{
      drawDoubleRaisedRectangle(dc,ix,iy,MENUGLYPH_WIDTH,MENUGLYPH_HEIGHT);
      }
    if(!label.empty()){
      dc.setFont(font);
      dc.setForeground(textColor);
      drawLabel(dc,label,hotoff,tx,ty,tw,th);
      }
    if(hasFocus()){
      dc.drawFocusRectangle(border+1,border+1,width-2*border-2,height-2*border-2);
      }
    }


  else{
    if(icon){
      dc.drawIconSunken(icon,ix,iy);
      }
    else{
      drawDoubleRaisedRectangle(dc,ix,iy,MENUGLYPH_WIDTH,MENUGLYPH_HEIGHT);
      }
    if(!label.empty()){
      dc.setFont(font);
      dc.setForeground(hiliteColor);
      drawLabel(dc,label,hotoff,tx+1,ty+1,tw,th);
      dc.setForeground(shadowColor);
      drawLabel(dc,label,hotoff,tx,ty,tw,th);
      }
    }
  return 1;
  }
