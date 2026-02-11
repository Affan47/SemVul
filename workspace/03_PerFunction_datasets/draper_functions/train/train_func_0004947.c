onKeyPress(FXObject*,FXSelector sel,void* ptr){
  FXEvent* event=(FXEvent*)ptr;
  flags&=~FLAG_TIP;
  if(isEnabled()){
    if(target && target->tryHandle(this,FXSEL(SEL_KEYPRESS,message),ptr)) return 1;
    if(pane && pane->shown() && pane->handle(pane,sel,ptr)) return 1;
    switch(event->code){
      case KEY_space:
      case KEY_KP_Space:
        return 1;
      }
    }
  return 0;
  }
