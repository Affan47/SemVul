onFocusUp(FXObject*,FXSelector,void*){
  if(pane && pane->shown()){
    handle(this,FXSEL(SEL_COMMAND,ID_UNPOST),NULL);
    return 1;
    }
  return 0;
  }
