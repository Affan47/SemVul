onCmdClose(FXObject*,FXSelector,void*){
  FXint result = FXMessageBox::question(this,MBOX_SAVE_CANCEL_DONTSAVE,"Save Changes?","Do you want to save changes to the FOX Registry\nbefore closing?\n\nIf you don't save, your changes will be lost.");
  if(result==MBOX_CLICKED_SAVE){
    saveFileBinding();
    writeDesktop();
    return 0;
    }
  else if(result==MBOX_CLICKED_CANCEL){
    return 1;
    }
  else{
    return 0;
    }
  return 0;
  }
