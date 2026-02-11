addHotKey(FXHotKey code){
  register FXAccelTable *accel=NULL;
  register FXWindow *win=this;
  while(win && (accel=win->getAccelTable())==NULL) win=win->parent;
  if(accel) accel->addAccel(code,this,FXSEL(SEL_KEYPRESS,ID_HOTKEY),FXSEL(SEL_KEYRELEASE,ID_HOTKEY));
  }
