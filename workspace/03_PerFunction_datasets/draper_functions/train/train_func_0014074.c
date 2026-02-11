onLeftBtnPress(FXObject*,FXSelector,void* ptr){
  handle(this,FXSEL(SEL_FOCUS_SELF,0),ptr);
  flags&=~FLAG_TIP;
  if(isEnabled()){
    if(state==STATE_UP){
      grab();
      setState(STATE_DOWN);
      flags&=~FLAG_UPDATE;
      }
    else{
      setState(STATE_UP);
      }
    return 1;
    }
  return 0;
  }
