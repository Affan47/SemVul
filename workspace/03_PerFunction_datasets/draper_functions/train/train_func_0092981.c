onCmdSize(FXObject*,FXSelector,void*ptr){
  selected.size=(FXuint)(FXuval)sizelist->getItemData((FXint)(FXival)ptr);
  sizefield->setText(sizelist->getItemText((FXint)(FXival)ptr));
  previewFont();
  return 1;
  }
