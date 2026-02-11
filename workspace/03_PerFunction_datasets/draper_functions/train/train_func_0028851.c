onCmdNewPlayList(FXObject*,FXSelector,void*){
  FXDialogBox dialog(GMPlayerManager::instance()->getMainWindow(),fxtr("Create Playlist"),DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE|DECOR_CLOSE,0,0,0,0,0,0,0,0,0,0);
  GMPlayerManager::instance()->getMainWindow()->create_dialog_header(&dialog,fxtr("Create Playlist"),fxtr("Specify name of the new playlist"),NULL);
  FXHorizontalFrame *closebox=new FXHorizontalFrame(&dialog,LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH,0,0,0,0);
  new GMButton(closebox,fxtr("&Create"),NULL,&dialog,FXDialogBox::ID_ACCEPT,BUTTON_INITIAL|BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 15,15);
  new GMButton(closebox,fxtr("&Cancel"),NULL,&dialog,FXDialogBox::ID_CANCEL,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 15,15);
  new FXSeparator(&dialog,SEPARATOR_GROOVE|LAYOUT_FILL_X|LAYOUT_SIDE_BOTTOM);
  FXVerticalFrame * main = new FXVerticalFrame(&dialog,LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0,30,20,10,10);
  FXMatrix * matrix = new FXMatrix(main,2,LAYOUT_FILL_X|MATRIX_BY_COLUMNS);
  new FXLabel(matrix,fxtr("Name"),NULL,LABEL_NORMAL|LAYOUT_RIGHT|LAYOUT_CENTER_Y);
  FXTextField * name_field = new GMTextField(matrix,20,&dialog,FXDialogBox::ID_ACCEPT,LAYOUT_FILL_X|LAYOUT_FILL_COLUMN|FRAME_SUNKEN|FRAME_THICK|TEXTFIELD_ENTER_ONLY);
  name_field->setText(fxtr("New Playlist"));
  name_field->setSelection(0,name_field->getText().length());
  dialog.create();
  gm_focus_and_select(name_field);
  if (dialog.execute()) {
    FXString label= name_field->getText().trim();
    if (!label.empty()) {
      FXint pl;
      db->insertPlaylist(label,pl);
      GMPlayerManager::instance()->insertSource(new GMPlayListSource(db,pl));
      GMPlayerManager::instance()->getSourceView()->refresh();
      }
    }
  return 1;
  }
