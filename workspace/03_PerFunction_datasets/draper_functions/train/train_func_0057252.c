onKeyPress(FXObject* sender,FXSelector sel,void* ptr){
  FXEvent* event=(FXEvent*)ptr;
  if(isEnabled()){
    if(target && target->tryHandle(this,FXSEL(SEL_KEYPRESS,message),ptr)) return 1;
    switch(event->code){
      case KEY_Up:
      case KEY_KP_Up:
        if(isEditable()){
          increment(TRUE);
          }
        else{
          getApp()->beep();
          }
        return 1;
      case KEY_Down:
      case KEY_KP_Down:
        if(isEditable()){
          decrement(TRUE);
          }
        else{
          getApp()->beep();
          }
        return 1;
      default:
        return textField->handle(sender,sel,ptr);
      }
    }
  return 0;
  }
