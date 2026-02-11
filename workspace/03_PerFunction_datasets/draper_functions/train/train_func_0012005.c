onUpdLineStyle(FXObject* sender,FXSelector sel,void*){
  FXLineStyle ff=(FXLineStyle)(LINE_SOLID+FXSELID(sel)-ID_LINE_SOLID);
  if(ff==lineStyle)
    sender->handle(this,FXSEL(SEL_COMMAND,ID_CHECK),NULL);
  else
    sender->handle(this,FXSEL(SEL_COMMAND,ID_UNCHECK),NULL);
  return 1;
  }
