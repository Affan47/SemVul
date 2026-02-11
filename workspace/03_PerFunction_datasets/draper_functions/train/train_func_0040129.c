onDNDMotion(FXObject* sender,FXSelector sel,void* ptr){
  FXEvent *event=(FXEvent*)ptr;
  FXTreeItem *item;


  if(startAutoScroll(event,FALSE)) return 1;


  if(FXTreeList::onDNDMotion(sender,sel,ptr)) return 1;


  if(offeredDNDType(FROM_DRAGNDROP,urilistType)){


    item=getItemAt(event->win_x,event->win_y);


    if(item && isItemDirectory(item)){


      dropdirectory=getItemPathname(item);


      dropaction=inquireDNDAction();


      if(FXStat::isWritable(dropdirectory)){
        FXTRACE((100,"accepting drop on %s\n",dropdirectory.text()));
        acceptDrop(DRAG_ACCEPT);
        }
      }
    return 1;
    }
  return 0;
  }
