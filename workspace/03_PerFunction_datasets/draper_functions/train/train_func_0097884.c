onCmdPost(FXObject*,FXSelector,void*){
  if(pane && !pane->shown()){
    FXint x,y;
    if(!current) current=dynamic_cast<FXOption*>(pane->getFirst());
    if(!current) return 1;
    translateCoordinatesTo(x,y,getRoot(),0,0);
    pane->position(x,y,width,pane->getDefaultHeight());
    y+=2-current->getY();
    pane->popup(this,x,y,width,pane->getDefaultHeight());
    current->setFocus();
    if(!grabbed()) grab();
    flags&=~FLAG_UPDATE;
    }
  return 1;
  }
