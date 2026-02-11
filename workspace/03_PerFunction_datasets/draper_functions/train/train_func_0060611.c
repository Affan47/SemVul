onHotKeyPress(FXObject*,FXSelector,void* ptr){
  handle(this,FXSEL(SEL_FOCUS_SELF,0),ptr);
  flags&=~FLAG_TIP;
  FXTRACE((100,"FXToggleButton::onHotKeyPress\n"));
  if(isEnabled() && !(flags&FLAG_PRESSED)){
    press(TRUE);
    flags|=FLAG_PRESSED;
    flags&=~FLAG_UPDATE;
    }
  return 1;
  }
