onBeginDrag(FXObject* sender,FXSelector sel,void* ptr){
  register FXTreeItem *item;
  if(FXTreeList::onBeginDrag(sender,sel,ptr)) return 1;
  if(beginDrag(&urilistType,1)){
    dragfiles=FXString::null;
    item=firstitem;
    while(item){
      if(item->isSelected()){
        if(!dragfiles.empty()) dragfiles+="\r\n";
        dragfiles+=FXURL::encode(FXURL::fileToURL(getItemPathname(item)));
        }
      if(item->first){
        item=item->first;
        }
      else{
        while(!item->next && item->parent) item=item->parent;
        item=item->next;
        }
      }
    return 1;
    }
  return 0;
  }
