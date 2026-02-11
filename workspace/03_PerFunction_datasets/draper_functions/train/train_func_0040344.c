grab(){
  if(xid){
    FXTRACE((150,"%s::grab %p\n",getClassName(),this));
    if(dragCursor->id()==0){ fxerror("%s::grab: Cursor has not been created yet.\n",getClassName()); }
    if(!(flags&FLAG_SHOWN)){ fxwarning("%s::grab: Window is not visible.\n",getClassName()); }
#ifndef WIN32
    if(GrabSuccess!=XGrabPointer(DISPLAY(getApp()),xid,FALSE,GRAB_EVENT_MASK,GrabModeAsync,GrabModeAsync,None,dragCursor->id(),getApp()->event.time)){
      XGrabPointer(DISPLAY(getApp()),xid,FALSE,GRAB_EVENT_MASK,GrabModeAsync,GrabModeAsync,None,dragCursor->id(),CurrentTime);
      }
#else
    SetCapture((HWND)xid);
    if(GetCapture()!=(HWND)xid){
      SetCapture((HWND)xid);
      }
    SetCursor((HCURSOR)dragCursor->id());
#endif
    getApp()->mouseGrabWindow=this;
    }
  }
