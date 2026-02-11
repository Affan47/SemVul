onRightBtnPress(FXObject*,FXSelector,void* ptr){
  FXEvent* event=(FXEvent*)ptr;
  flags&=~FLAG_TIP;
  FXTRACE((100,"onRightBtnPress Mask=%08x\n",event->state));
  handle(this,FXSEL(SEL_FOCUS_SELF,0),ptr);
  if(isEnabled()){
    grab();
    flags&=~FLAG_UPDATE;
    if(target && target->tryHandle(this,FXSEL(SEL_RIGHTBUTTONPRESS,message),ptr)) return 1;
    if(event->state&LEFTBUTTONMASK){
      if(event->state&SHIFTMASK){
        setOp(TRUCKING);
        }
      else{
        setOp(ZOOMING);
        }
      }
    else if(event->state&MIDDLEBUTTONMASK){
      if(event->state&SHIFTMASK){
        setOp(GYRATING);
        }
      else if(event->state&CONTROLMASK){
        setOp(FOVING);
        }
      else{
        setOp(TRANSLATING);
        }
      }
    else{
      if(event->state&SHIFTMASK){
        setOp(GYRATING);
        }
      else if(event->state&CONTROLMASK){
        setOp(FOVING);
        }
      else{
        setOp(POSTING);
        }
      }
    }
  return 1;
  }
