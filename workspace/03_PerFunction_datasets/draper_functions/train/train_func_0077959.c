onCmdUnpost(FXObject*,FXSelector,void* ptr){
  FXTRACE((150,"%s::onCmdUnpost %p\n",getClassName(),this));
  if(grabowner){
    grabowner->handle(this,FXSEL(SEL_COMMAND,ID_UNPOST),ptr);
    }
  else{
    popdown();
    if(grabbed()) ungrab();
    }
  return 1;
  }
