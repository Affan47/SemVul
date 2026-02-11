onLeave(FXObject* sender,FXSelector sel,void* ptr){
  FXFrame::onLeave(sender,sel,ptr);
  if(isEnabled()){
    if(flags&FLAG_PRESSED){
      setState(FALSE);
      }
    else if(options&ARROW_AUTO){
      setState(FALSE);
      if(options&ARROW_REPEAT) getApp()->removeTimeout(this,ID_AUTO);
      flags|=FLAG_UPDATE;
      fired=FALSE;
      }
    if(options&ARROW_TOOLBAR) update();
    }
  return 1;
  }
