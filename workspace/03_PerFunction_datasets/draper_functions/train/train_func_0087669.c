setLineCap(FXCapStyle capstyle){
  XGCValues gcv;
  if(!surface){ fxerror("FXDCWindow::setLineCap: DC not connected to drawable.\n"); }
  gcv.cap_style=capstyle;
  XChangeGC(DISPLAY(getApp()),(GC)ctx,GCCapStyle,&gcv);
  flags|=GCCapStyle;
  cap=capstyle;
  }
