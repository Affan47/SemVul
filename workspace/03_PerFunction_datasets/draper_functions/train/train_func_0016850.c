onUpdSortCase(FXObject* sender,FXSelector,void*){
  sender->handle(this,(sortfunc==ascendingCase || sortfunc==descendingCase) ? FXSEL(SEL_COMMAND,ID_CHECK) : FXSEL(SEL_COMMAND,ID_UNCHECK),NULL);
  sender->handle(this,(sortfunc==ascendingCase || sortfunc==ascending || sortfunc==descendingCase || sortfunc==descending) ? FXSEL(SEL_COMMAND,ID_ENABLE) : FXSEL(SEL_COMMAND,ID_DISABLE),NULL);
  return 1;
  }
