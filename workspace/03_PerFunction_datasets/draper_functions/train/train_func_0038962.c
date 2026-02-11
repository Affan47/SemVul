onMotion(FXObject*,FXSelector,void* ptr){
  FXEvent* ev=(FXEvent*)ptr;
  if(pane && pane->shown()){
    if(pane->contains(ev->root_x,ev->root_y)){
      if(grabbed()) ungrab();
      }
    else{
      if(!grabbed()) grab();
      }
    return 1;
    }
  return 0;
  }
