grabKeyboard(){
  if(xid){
    FXTRACE((150,"%s::grabKeyboard %p\n",getClassName(),this));
    if(!(flags&FLAG_SHOWN)){ fxwarning("%s::ungrabKeyboard: Window is not visible.\n",getClassName()); }
#ifndef WIN32
    XGrabKeyboard(DISPLAY(getApp()),xid,FALSE,GrabModeAsync,GrabModeAsync,getApp()->event.time);
#else
    SetActiveWindow((HWND)xid);
#endif
    getApp()->keyboardGrabWindow=this;
    }
  }
