onSelectionRequest(FXObject*,FXSelector,void* ptr){
  FXTRACE((100,"%s::onSelectionRequest %p\n",getClassName(),this));
  return target && target->tryHandle(this,FXSEL(SEL_SELECTION_REQUEST,message),ptr);
  }
