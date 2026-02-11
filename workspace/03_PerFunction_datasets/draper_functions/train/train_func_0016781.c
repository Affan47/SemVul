onMotion(FXObject*,FXSelector,void* ptr){
  FXEvent* ev=(FXEvent*)ptr;
  FXint px,py;
  if(!getFocus() || !getFocus()->isActive()) return 0;
  translateCoordinatesTo(px,py,getParent(),ev->win_x,ev->win_y);
  if(contains(px,py)){
    if(grabbed()) ungrab();
    }
  else{
    if(!grabbed()) grab();
    }
  return 0;
  }
