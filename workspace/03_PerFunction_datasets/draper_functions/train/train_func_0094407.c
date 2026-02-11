onFocusDown(FXObject*,FXSelector,void* ptr){
  register FXWindow *child;
  register FXint r,c;
  if(getFocus()){
    r=rowOfChild(getFocus());
    c=colOfChild(getFocus());
    while((child=childAtRowCol(++r,c))!=NULL){
      if(child->shown()){
        if(child->handle(this,FXSEL(SEL_FOCUS_SELF,0),ptr)) return 1;
        if(child->handle(this,FXSEL(SEL_FOCUS_DOWN,0),ptr)) return 1;
        }
      }
    }
  else{
    child=getFirst();
    while(child){
      if(child->shown()){
        if(child->handle(this,FXSEL(SEL_FOCUS_SELF,0),ptr)) return 1;
        if(child->handle(this,FXSEL(SEL_FOCUS_DOWN,0),ptr)) return 1;
        }
      child=child->getNext();
      }
    }
  return 0;
  }
