onLeftBtnRelease(FXObject*,FXSelector,void* ptr){
  FXEvent* ev=(FXEvent*)ptr;
  flags&=~FLAG_TIP;
  if(isEnabled()){
    if(target && target->tryHandle(this,FXSEL(SEL_LEFTBUTTONRELEASE,message),ptr)) return 1;
    if(ev->moved && pane){ handle(this,FXSEL(SEL_COMMAND,ID_UNPOST),NULL); }
    return 1;
    }
  return 0;
  }
