onCmdCutSel(FXObject*,FXSelector,void*){
  if(isEditable()){
    if(selstartpos<selendpos){
      FXDragType types[4];
      types[0]=stringType;
      types[1]=textType;
      types[2]=utf8Type;
      types[3]=utf16Type;
      if(acquireClipboard(types,4)){
        FXASSERT(selstartpos<=selendpos);
        extractText(clipped,selstartpos,selendpos-selstartpos);
        handle(this,FXSEL(SEL_COMMAND,ID_DELETE_SEL),NULL);
        }
      }
    }
  else{
    getApp()->beep();
    }
  return 1;
  }
