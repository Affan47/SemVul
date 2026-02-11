onMotion(FXObject*,FXSelector,void* ptr){
  register FXEvent *event=(FXEvent*)ptr;
  register FXint p;
  if(!isEnabled()) return 0;
  if(flags&FLAG_PRESSED){
    p=calcValue(event->win_x,event->win_y);
    if(pos!=p){
      setValue(p);
      flags|=FLAG_CHANGED;
      if(target) target->tryHandle(this,FXSEL(SEL_CHANGED,message),(void*)(FXival)pos);
      }
    return 1;
    }
  return 0;
  }
