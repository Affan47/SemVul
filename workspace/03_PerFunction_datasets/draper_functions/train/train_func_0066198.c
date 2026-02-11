onCmdMoveLeft(FXObject*,FXSelector,void*){
  if(current.col<1) return 1;
  setCurrentItem(current.row,current.col-1,TRUE);
  makePositionVisible(current.row,current.col);
  return 1;
  }
