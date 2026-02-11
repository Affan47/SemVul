restore(FXbool notify){
  if(isMinimized() || isMaximized()){
    if(xid){
#ifdef WIN32
      ShowWindow((HWND)xid,SW_RESTORE);
#else
      XEvent se;
      se.xclient.type=ClientMessage;
      se.xclient.display=DISPLAY(getApp());
      se.xclient.message_type=getApp()->wmNetState;
      se.xclient.format=32;
      se.xclient.window=xid;
      se.xclient.data.l[0]=0;
      se.xclient.data.l[1]=getApp()->wmNetHMaximized;
      se.xclient.data.l[2]=getApp()->wmNetVMaximized;
      se.xclient.data.l[3]=0;
      se.xclient.data.l[4]=0;
      XSendEvent(DISPLAY(getApp()),XDefaultRootWindow(DISPLAY(getApp())),False,SubstructureRedirectMask|SubstructureNotifyMask,&se);
      XMapWindow(DISPLAY(getApp()),xid);
#endif
      }
    if(notify && target){target->tryHandle(this,FXSEL(SEL_RESTORE,message),NULL);}
    return TRUE;
    }
  return FALSE;
  }
