fxsenddata(Display *display,Window window,Atom prop,Atom type,FXuchar* data,FXuint size){
  unsigned long maxtfrsize,tfrsize,tfroffset;
  int mode;
  if(data && size){
    maxtfrsize=4*XMaxRequestSize(display);
    mode=PropModeReplace;
    tfroffset=0;
    while(size){
      tfrsize=size;
      if(tfrsize>maxtfrsize) tfrsize=maxtfrsize;
      XChangeProperty(display,window,prop,type,8,mode,&data[tfroffset],tfrsize);
      mode=PropModeAppend;
      tfroffset+=tfrsize;
      size-=tfrsize;
      }
    return prop;
    }
  return None;
  }
