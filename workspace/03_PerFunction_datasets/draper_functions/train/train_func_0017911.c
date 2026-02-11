onMotion(FXObject*,FXSelector,void* ptr){
  if(flags&FLAG_DODRAG){
    handle(this,FXSEL(SEL_DRAGGED,0),ptr);
    return 1;
    }
  if((flags&FLAG_TRYDRAG) && ((FXEvent*)ptr)->moved){
    if(handle(this,FXSEL(SEL_BEGINDRAG,0),ptr)) flags|=FLAG_DODRAG;
    flags&=~FLAG_TRYDRAG;
    return 1;
    }
  return 0;
  }
