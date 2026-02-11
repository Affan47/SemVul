onHotKeyRelease(FXObject*,FXSelector,void*){
  FXTRACE((100,"FXToggleButton::onHotKeyRelease\n"));
  if(isEnabled() && (flags&FLAG_PRESSED)){
    flags|=FLAG_UPDATE;
    flags&=~FLAG_PRESSED;
    press(FALSE);
    setState(!state);
    if(target) target->tryHandle(this,FXSEL(SEL_COMMAND,message),(void*)(FXuval)state);
    }
  return 1;
  }
