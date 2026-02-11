acquire(FXObject * owner,const FXDragType * types,FXuint num_types,GMClipboardData * data){
  if (acquireClipboard(types,num_types)){

    clipowner=owner;
    clipdata=data;
    return true;
    }
  return false;
  }
