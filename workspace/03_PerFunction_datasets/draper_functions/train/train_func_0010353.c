onUpdLeft(FXObject* sender,FXSelector,void*){
  sender->handle(this,FXSEL(SEL_COMMAND,ID_SHOW),NULL);
  sender->handle(this,FXSEL(SEL_COMMAND,ID_ENABLE),NULL);
  sender->handle(this,(EPS>fabs(rotation[0]) && EPS>fabs(rotation[1]-0.7071067811865) && EPS>fabs(rotation[2]) && EPS>fabs(rotation[3]-0.7071067811865)) ? FXSEL(SEL_COMMAND,ID_CHECK) : FXSEL(SEL_COMMAND,ID_UNCHECK),NULL);
  return 1;
  }
