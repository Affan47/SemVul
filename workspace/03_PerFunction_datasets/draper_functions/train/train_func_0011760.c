onButtonRelease(FXObject*,FXSelector,void*){
  FXbool active=isActive();
  if(!isEnabled()) return 0;
  if(active){
    setCheck(!check);
    if(target){ target->tryHandle(this,FXSEL(SEL_COMMAND,message),(void*)(FXuval)check); }
    }
  return 1;
  }
