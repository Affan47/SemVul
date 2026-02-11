onTrackContextMenu(FXObject*,FXSelector,void*ptr){
  FXEvent * event = reinterpret_cast<FXEvent*>(ptr);
  if (source && !event->moved) {
    GMMenuPane pane(this);
    FXint item = tracklist->getItemAt(event->win_x,event->win_y);
    if (item>=0 && !tracklist->isItemSelected(item))
      selectTrackItem(item);

    if (item>=0 && source->track_context_menu(&pane))
      new FXMenuSeparator(&pane);

    new GMMenuCascade(&pane,tr("&Columns\t\tChange Visible Columns."),NULL,columnmenu);
    new GMMenuCascade(&pane,tr("&Sort\t\tChange Sorting."),GMIconTheme::instance()->icon_sort,sortmenu);

    pane.create();
    ewmh_change_window_type(columnmenu,WINDOWTYPE_DROPDOWN_MENU);
    ewmh_change_window_type(sortmenu,WINDOWTYPE_DROPDOWN_MENU);
    ewmh_change_window_type(&pane,WINDOWTYPE_POPUP_MENU);
    pane.popup(NULL,event->root_x+3,event->root_y+3);
    getApp()->runPopup(&pane);
    return 1;
    }
  return 0;
  }
