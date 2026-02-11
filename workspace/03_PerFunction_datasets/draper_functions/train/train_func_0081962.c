onMotion(FXObject*,FXSelector,void* ptr){
  FXEvent* event=(FXEvent*)ptr;
  FXint oldcursor=cursor;
  FXuint flg=flags;


  flags&=~FLAG_TIP;


  getApp()->removeTimeout(this,ID_TIPTIMER);


  if(flags&FLAG_SCROLLING){
    setPosition(event->win_x-grabx,event->win_y-graby);
    return 1;
    }


  if(flags&FLAG_DODRAG){
    if(startAutoScroll(event,TRUE)) return 1;
    handle(this,FXSEL(SEL_DRAGGED,0),ptr);
    return 1;
    }


  if((flags&FLAG_TRYDRAG) && event->moved){
    flags&=~FLAG_TRYDRAG;
    if(handle(this,FXSEL(SEL_BEGINDRAG,0),ptr)){
      flags|=FLAG_DODRAG;
      }
    return 1;
    }


  if((flags&FLAG_PRESSED) || (options&LIST_AUTOSELECT)){


    if(startAutoScroll(event,FALSE)) return 1;


    FXint index=getItemAt(event->win_x,event->win_y);


    if(0<=index && index!=current){


      setCurrentItem(index,TRUE);


      if((options&SELECT_MASK)==LIST_EXTENDEDSELECT){
        state=FALSE;
        extendSelection(index,TRUE);
        }
      return 1;
      }
    }


  getApp()->addTimeout(this,ID_TIPTIMER,getApp()->getMenuPause());


  cursor=getItemAt(event->win_x,event->win_y);


  return (cursor!=oldcursor)||(flg&FLAG_TIP);
  }
