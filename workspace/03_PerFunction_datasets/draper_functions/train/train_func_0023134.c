onFocusPrev(FXObject* sender,FXSelector sel,void* ptr){
  return (options&SPLITTER_VERTICAL) ? onFocusUp(sender,sel,ptr) : onFocusLeft(sender,sel,ptr);
  }
