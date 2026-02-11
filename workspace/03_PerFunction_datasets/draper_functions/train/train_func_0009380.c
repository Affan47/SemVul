onUpdClear(FXObject* sender,FXSelector,void*){
  sender->handle(this,(canUndo()||canRedo())?FXSEL(SEL_COMMAND,FXWindow::ID_ENABLE):FXSEL(SEL_COMMAND,FXWindow::ID_DISABLE),NULL);
  return 1;
  }
