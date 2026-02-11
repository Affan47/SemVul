setForeground(FXColor clr){
  if(!surface){ fxerror("FXDCWindow::setForeground: DC not connected to drawable.\n"); }
  devfg=visual->getPixel(clr);
  XSetForeground(DISPLAY(getApp()),(GC)ctx,devfg);
  flags|=GCForeground;
  fg=clr;
  }
