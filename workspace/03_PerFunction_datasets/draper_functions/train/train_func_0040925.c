onCmdDeleteSel(FXObject*,FXSelector,void*){
  if(isEditable()){
    if(selstartpos<selendpos){
      removeText(selstartpos,selendpos-selstartpos,TRUE);
      killSelection(TRUE);
      setCursorPos(cursorpos,TRUE);
      makePositionVisible(cursorpos);
      flags|=FLAG_CHANGED;
      modified=TRUE;
      }
    }
  else{
    getApp()->beep();
    }
  return 1;
  }
