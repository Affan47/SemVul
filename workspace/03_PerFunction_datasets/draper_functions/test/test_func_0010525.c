onCmdBookmark(FXObject*,FXSelector,void*){
  bookmarks.appendFile(getDirectory());
  return 1;
  }
