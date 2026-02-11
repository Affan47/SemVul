onCmdAccel(FXObject*,FXSelector,void*){
  if(isEnabled()){
    if(target) target->tryHandle(this,FXSEL(SEL_COMMAND,message),(void*)(FXuval)1);
    return 1;
    }
  return 0;
  }
