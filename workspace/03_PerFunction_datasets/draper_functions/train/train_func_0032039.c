onAlbumContextMenu(FXObject*,FXSelector,void*ptr){
  FXEvent * event = reinterpret_cast<FXEvent*>(ptr);
  FXbool old = album_by_year;
  FXDataTarget target_yearsort(album_by_year);
  if (source && !event->moved) {
    GMMenuPane pane(this);
    FXint item = albumlist->getItemAt(event->win_x,event->win_y);
    if (item>=0 && getAlbum(item)!=-1 && source->album_context_menu(&pane))
      selectAlbumItem(item);
    new GMMenuCheck(&pane,fxtr("Sort by Album Year"),&target_yearsort,FXDataTarget::ID_VALUE);
    pane.create();
    pane.forceRefresh();
    ewmh_change_window_type(&pane,WINDOWTYPE_POPUP_MENU);
    pane.popup(NULL,event->root_x+3,event->root_y+3);
    getApp()->runPopup(&pane);

    if (old!=album_by_year){
      sortAlbums();
      sortTracks();
      }
    return 1;
    }
  return 0;
  }
