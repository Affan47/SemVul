onKeyRelease(FXObject*,FXSelector,void* ptr){
  FXEvent* event=(FXEvent*)ptr;
  if(isEnabled() && (flags&FLAG_PRESSED)){
    if(target && target->tryHandle(this,FXSEL(SEL_KEYRELEASE,message),ptr)) return 1;
    if(event->code==KEY_space || event->code==KEY_KP_Space){
      flags|=FLAG_UPDATE;
      flags&=~FLAG_PRESSED;
      if(check!=oldcheck && target){ target->tryHandle(this,FXSEL(SEL_COMMAND,message),(void*)(FXuval)check); }
      return 1;
      }
    }
  return 0;
  }
