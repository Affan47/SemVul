onMiddleBtnPress(FXObject*,FXSelector,void* ptr){
  FXEvent* ev=(FXEvent*)ptr;
  flags&=~FLAG_TIP;
  handle(this,FXSEL(SEL_FOCUS_SELF,0),ptr);
  if(isEnabled()){
    grab();
    if(target && target->tryHandle(this,FXSEL(SEL_MIDDLEBUTTONPRESS,message),ptr)) return 1;
    setCursorPos(index(ev->win_x));
    setAnchorPos(cursor);
    makePositionVisible(cursor);
    update(border,border,width-(border<<1),height-(border<<1));
    flags&=~FLAG_UPDATE;
    return 1;
    }
  return 0;
  }
