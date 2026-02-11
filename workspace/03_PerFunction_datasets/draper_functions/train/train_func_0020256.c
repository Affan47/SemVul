onButtonRelease(FXObject*,FXSelector,void*){
  FXbool active=isActive();
  if(!isEnabled()) return 0;
  getParent()->handle(this,FXSEL(SEL_COMMAND,ID_UNPOST),NULL);
  if(active && target){ target->tryHandle(this,FXSEL(SEL_COMMAND,message),(void*)(FXuval)1); }
  return 1;
  }
