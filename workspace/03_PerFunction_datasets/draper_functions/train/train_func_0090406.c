onFocusIn(FXObject* sender,FXSelector sel,void* ptr){
  FXint fh,mh,bh,th;
  FXComposite::onFocusIn(sender,sel,ptr);
  fh=font->getFontHeight();
  mh=windowbtn->getDefaultHeight();
  bh=deletebtn->getDefaultHeight();
  th=FXMAX3(fh,mh,bh)+2;
  windowbtn->setBackColor(isActive() ? titleBackColor : backColor);
  update(BORDERWIDTH,BORDERWIDTH,width-(BORDERWIDTH<<1),th);
  return 1;
  }
