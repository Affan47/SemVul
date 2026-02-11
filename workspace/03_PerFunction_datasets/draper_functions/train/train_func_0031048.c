onCmdColorPick(FXObject*,FXSelector,void* ptr){
  FXPoint *point=(FXPoint*)ptr;
  FXDCWindow dc(getRoot());
  setRGBA(dc.readPixel(point->x,point->y));
  if(target) target->tryHandle(this,FXSEL(SEL_COMMAND,message),(void*)(FXuval)well->getRGBA());
  return 1;
  }
