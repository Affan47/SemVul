initdialog(){
  dirbox=new FXDirSelector(this,NULL,0,LAYOUT_FILL_X|LAYOUT_FILL_Y);
  dirbox->acceptButton()->setTarget(this);
  dirbox->acceptButton()->setSelector(FXDialogBox::ID_ACCEPT);
  dirbox->cancelButton()->setTarget(this);
  dirbox->cancelButton()->setSelector(FXDialogBox::ID_CANCEL);
  setWidth(getApp()->reg().readIntEntry("Directory Dialog","width",getWidth()));
  setHeight(getApp()->reg().readIntEntry("Directory Dialog","height",getHeight()));
  }
