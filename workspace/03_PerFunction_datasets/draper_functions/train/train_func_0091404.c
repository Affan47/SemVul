onCmdConfigureColumns(FXObject*,FXSelector,void*){
  GMColumnDialog dialog(getShell(),columns);
  if (dialog.execute()) {
    dialog.saveIndex();

    tracklist->clearHeaders();
    for (FXint i=0;i<columns.no();i++){
      if (columns[i].show) {
        tracklist->appendHeader(fxtr(columns[i].name.text()),columns[i].size,&columns[i]);
        }
      }


    }
  return 1;
  }
