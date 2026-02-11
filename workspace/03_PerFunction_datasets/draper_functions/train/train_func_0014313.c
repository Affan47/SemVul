onHotKeyRelease(FXObject*,FXSelector,void*){
  FXTRACE((200,"%s::onHotKeyRelease %p\n",getClassName(),this));
  if(isEnabled() && (flags&FLAG_PRESSED)){
    flags&=~FLAG_PRESSED;
    setCheck(!check);
    getParent()->handle(this,FXSEL(SEL_COMMAND,ID_UNPOST),NULL);
    if(target) target->tryHandle(this,FXSEL(SEL_COMMAND,message),(void*)(FXuval)check);
    }
  return 1;
  }
