detach(){


  visual->detach();


  if(defaultCursor) defaultCursor->detach();


  if(dragCursor) dragCursor->detach();

  if(xid){
    if(getApp()->isInitialized()){
      FXTRACE((100,"%s::detach %p\n",getClassName(),this));


      getApp()->hash.remove((void*)xid);
      }


    if(getApp()->mouseGrabWindow==this) getApp()->mouseGrabWindow=NULL;
    if(getApp()->keyboardGrabWindow==this) getApp()->keyboardGrabWindow=NULL;
    if(getApp()->cursorWindow==this) getApp()->cursorWindow=parent;
    if(getApp()->activeWindow==this) getApp()->activeWindow=NULL;
    flags&=~FLAG_FOCUSED;
    flags&=~FLAG_OWNED;
    xid=0;
    }
  }
