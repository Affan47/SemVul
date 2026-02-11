onRightBtnPress(FXObject*,FXSelector,void* ptr){
  flags&=~FLAG_TIP;
  if(isEnabled()){
    grab();
    if(target && target->tryHandle(this,FXSEL(SEL_RIGHTBUTTONPRESS,message),ptr)) return 1;
    lower();
    return 1;
    }
  return 0;
  }
