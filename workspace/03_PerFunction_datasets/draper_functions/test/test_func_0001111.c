onClipboardRequest(FXObject*,FXSelector,void*ptr){
  FXEvent *event=(FXEvent*)ptr;

  if (clipdata && clipdata->request(event->target,this)){
    return 1;
    }
  return 0;
  }
