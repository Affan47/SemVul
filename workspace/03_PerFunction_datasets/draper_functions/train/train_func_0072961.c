onCmdPaste(FXObject*,FXSelector,void*){
  FXString     files;
  FXStringList filelist;
  FXDragType * types;
  FXuint       num;

  FXbool       from_kde=false;
  FXbool       from_gnome=false;
  FXbool       from_uri=false;

  GMClipboard * clipboard = GMClipboard::instance();

  if (clipboard->inquireDNDTypes(FROM_CLIPBOARD,types,num)){

    for (FXuint i=0;i<num;i++) {
      if (types[i]==GMClipboard::kdeclipboard)
        from_kde=true;
      else if (types[i]==GMClipboard::gnomeclipboard)
        from_gnome=true;
      else if (types[i]==FXWindow::urilistType)
        from_uri=true;
      }

    freeElms(types);

    if ((from_gnome || from_uri || from_kde) && clipboard->hasClipboard() ) {
      return 1;
      }

    if (from_gnome) {
      if (clipboard->getDNDData(FROM_CLIPBOARD,GMClipboard::gnomeclipboard,files)){
        gm_convert_gnomeclipboard_to_filenames(files,filelist);
        }
      }
    else if (from_kde && from_uri) {
      if (clipboard->getDNDData(FROM_CLIPBOARD,GMClipboard::kdeclipboard,files)){
#ifdef DEBUG
        if (files=="1") {
          fxmessage("We do not cut files...\n");
          }
#endif
        }
      if (clipboard->getDNDData(FROM_CLIPBOARD,FXWindow::urilistType,files)){
        gm_convert_uri_to_filenames(files,filelist);
        }
      }

    if (filelist.no()){
      GMImportDialog dialog(GMPlayerManager::instance()->getMainWindow(),IMPORT_FROMPASTE);
      if (dialog.execute()) {
        GMPlayerManager::instance()->stop();
        GMImportDatabase searchdialog(GMPlayerManager::instance()->getMainWindow(),filelist,GMPlayerManager::instance()->getPreferences().import,getPlayList(),GMPlayerManager::instance()->getMainWindow()->getThickFont());
        searchdialog.execute();
        GMPlayerManager::instance()->getTrackView()->refresh();
        }
      }
    else {
      FXApp::instance()->beep();
      }

    return 1;
    }
  return 0;
  }
