onCmdSplit(FXObject*,FXSelector,void*){
  if(0<=sellower && 0<=selupper){
    splitSegments(sellower,selupper,TRUE);
    selectSegments(sellower,selupper+selupper-sellower+1,TRUE);
    }
  return 1;
  }
