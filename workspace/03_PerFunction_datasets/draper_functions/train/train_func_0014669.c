acceptDrop(FXDragAction action) const {
  getApp()->ansAction=DRAG_REJECT;
  if(action!=DRAG_REJECT){
    getApp()->ansAction=getApp()->ddeAction;
    if(action!=DRAG_ACCEPT) getApp()->ansAction=action;
    }
  }
