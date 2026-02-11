onCmdFamily(FXObject*,FXSelector,void* ptr){
  strncpy(selected.face,familylist->getItemText((FXint)(FXival)ptr).text(),sizeof(selected.face));
  listFontStyle();
  listFontSize();
  previewFont();
  return 1;
  }
