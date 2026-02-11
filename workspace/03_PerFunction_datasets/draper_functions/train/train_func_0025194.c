onCmdDeleteAll(FXObject*,FXSelector,void*){
  if(isEditable()){
    removeText(0,length,TRUE);
    setCursorPos(0,TRUE);
    makePositionVisible(0);
    flags|=FLAG_CHANGED;
    modified=TRUE;
    }
  else{
    getApp()->beep();
    }
  return 1;
  }
