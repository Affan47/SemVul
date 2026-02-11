onFocusNext(FXObject* sender,FXSelector,void* ptr){
  FXWindow *child;
  if(getFocus()){
    child=getFocus()->getNext();
    while(child){
      if(child->shown()){
        if(child->handle(this,FXSEL(SEL_FOCUS_SELF,0),ptr)) return 1;
        if(child->handle(sender,FXSEL(SEL_FOCUS_NEXT,0),ptr)) return 1;
        }
      child=child->getNext();
      }
    getFocus()->killFocus();
    }
  child=getFirst();
  while(child){
    if(child->shown()){
      if(child->handle(this,FXSEL(SEL_FOCUS_SELF,0),ptr)) return 1;
      if(child->handle(sender,FXSEL(SEL_FOCUS_NEXT,0),ptr)) return 1;
      }
    child=child->getNext();
    }
  return 0;
  }
