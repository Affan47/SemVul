onCmdShiftText(FXObject*,FXSelector sel,void*){
  if(isEditable()){
    FXint start,end,len,amount;
    amount=0;
    switch(FXSELID(sel)){
      case ID_SHIFT_LEFT: amount=-1; break;
      case ID_SHIFT_RIGHT: amount=1; break;
      case ID_SHIFT_TABLEFT: amount=-tabcolumns; break;
      case ID_SHIFT_TABRIGHT: amount=tabcolumns; break;
      }
    if(selstartpos<selendpos){
      FXASSERT(0<=selstartpos && selstartpos<=length);
      FXASSERT(0<=selendpos && selendpos<=length);
      start=lineStart(selstartpos);
      end=selendpos;
      if(0<end && getByte(end-1)!='\n') end=nextLine(end);
      }
    else{
      start=lineStart(cursorpos);
      end=lineEnd(cursorpos);
      if(end<length) end++;
      }
    len=shiftText(start,end,amount,TRUE);
    setAnchorPos(start);
    extendSelection(start+len,SELECT_CHARS,TRUE);
    setCursorPos(start,TRUE);
    flags|=FLAG_CHANGED;
    modified=TRUE;
    }
  else{
    getApp()->beep();
    }
  return 1;
  }
