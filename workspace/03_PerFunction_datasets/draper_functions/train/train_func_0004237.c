onPopupMenu(FXObject*,FXSelector,void* ptr){
  FXEvent* event=static_cast<FXEvent*>(ptr);
  if(event->moved) return 1;
  FXMenuPane dockmenu(this);
  FXGIFIcon dockflipicon(getApp(),dockflip);
  FXGIFIcon docktopicon(getApp(),docktop,FXRGB(255,255,255),IMAGE_ALPHACOLOR);
  FXGIFIcon dockbottomicon(getApp(),dockbottom,FXRGB(255,255,255),IMAGE_ALPHACOLOR);
  FXGIFIcon docklefticon(getApp(),dockleft,FXRGB(255,255,255),IMAGE_ALPHACOLOR);
  FXGIFIcon dockrighticon(getApp(),dockright,FXRGB(255,255,255),IMAGE_ALPHACOLOR);
  FXGIFIcon dockfreeicon(getApp(),dockfree,FXRGB(255,255,255),IMAGE_ALPHACOLOR);
  new FXMenuCaption(&dockmenu,tr("Docking"));
  new FXMenuSeparator(&dockmenu);
  new FXMenuCommand(&dockmenu,tr("Top"),&docktopicon,this,ID_DOCK_TOP);
  new FXMenuCommand(&dockmenu,tr("Bottom"),&dockbottomicon,this,ID_DOCK_BOTTOM);
  new FXMenuCommand(&dockmenu,tr("Left"),&docklefticon,this,ID_DOCK_LEFT);
  new FXMenuCommand(&dockmenu,tr("Right"),&dockrighticon,this,ID_DOCK_RIGHT);
  new FXMenuCommand(&dockmenu,tr("Float"),&dockfreeicon,this,ID_DOCK_FLOAT);
  new FXMenuCommand(&dockmenu,tr("Flip"),&dockflipicon,this,ID_DOCK_FLIP);
  dockmenu.create();
  dockmenu.popup(NULL,event->root_x,event->root_y);


  dockmenu.forceRefresh();
  getApp()->runModalWhileShown(&dockmenu);
  return 1;
  }
