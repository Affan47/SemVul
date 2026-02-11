dropFinished(FXDragAction action) const {
  if(!getApp()->xdndFinishSent){
#ifndef WIN32
    XEvent se;
    se.xclient.type=ClientMessage;
    se.xclient.display=DISPLAY(getApp());
    se.xclient.message_type=getApp()->xdndFinished;
    se.xclient.format=32;
    se.xclient.window=getApp()->xdndSource;
    se.xclient.data.l[0]=xid;
    se.xclient.data.l[1]=(action==DRAG_REJECT)?0:1;
    if(action==DRAG_ACCEPT) action=getApp()->ansAction;
    if(action==DRAG_COPY) se.xclient.data.l[2]=getApp()->xdndActionCopy;
    else if(action==DRAG_MOVE) se.xclient.data.l[2]=getApp()->xdndActionMove;
    else if(action==DRAG_LINK) se.xclient.data.l[2]=getApp()->xdndActionLink;
    else if(action==DRAG_PRIVATE) se.xclient.data.l[2]=getApp()->xdndActionPrivate;
    else se.xclient.data.l[2]=None;
    se.xclient.data.l[3]=0;
    se.xclient.data.l[4]=0;
    XSendEvent(DISPLAY(getApp()),getApp()->xdndSource,True,NoEventMask,&se);
    XFlush(DISPLAY(getApp()));
#else
    if(action==DRAG_ACCEPT) action=getApp()->ansAction;
    PostMessage((HWND)getApp()->xdndSource,WM_DND_FINISH_REJECT+action,0,(LPARAM)xid);
#endif
    getApp()->xdndFinishSent=TRUE;
    }
  }
