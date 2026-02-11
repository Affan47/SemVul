onButtonPress(FXObject*,FXSelector,void*){
  if(!isEnabled()) return 0;
  handle(this,FXSEL(SEL_COMMAND,ID_POST),NULL);
  return 1;
  }
