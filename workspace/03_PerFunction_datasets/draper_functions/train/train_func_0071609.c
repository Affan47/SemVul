onUpdUniform(FXObject* sender,FXSelector,void*){
  sender->handle(this,(0<=sellower && 0<=selupper)?FXSEL(SEL_COMMAND,ID_ENABLE):FXSEL(SEL_COMMAND,ID_DISABLE),NULL);
  return 1;
  }
