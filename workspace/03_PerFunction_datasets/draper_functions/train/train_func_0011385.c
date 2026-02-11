onLeftBtnRelease(FXObject* sender,FXSelector sel,void* ptr){
  FXbool click=down;
  if(!FXFrame::onLeftBtnRelease(sender,sel,ptr)){
    if(isEnabled() && (flags&FLAG_PRESSED)){
      flags|=FLAG_UPDATE;
      flags&=~FLAG_PRESSED;
      down=FALSE;
      update();
      if(click) collapse(!collapsed,TRUE);
      return 1;
      }
    }
  return 0;
  }
