onLeftBtnPress(FXObject*,FXSelector,void* ptr){
  flags&=~FLAG_TIP;
  handle(this,FXSEL(SEL_FOCUS_SELF,0),ptr);
  if(isEnabled()){
    if(target && target->tryHandle(this,FXSEL(SEL_LEFTBUTTONPRESS,message),ptr)) return 1;
    if(state)
      handle(this,FXSEL(SEL_COMMAND,ID_UNPOST),NULL);
    else
      handle(this,FXSEL(SEL_COMMAND,ID_POST),NULL);
    return 1;
    }
  return 0;
  }
