getSplit(FXint index) const {
  FXWindow *win=childAtIndex(index);
  if(win){
    if(options&SPLITTER_VERTICAL){
      return win->getHeight();
      }
    else{
      return win->getWidth();
      }
    }
  return 0;
  }
