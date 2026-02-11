onCmdSortByType(FXObject*,FXSelector,void*){
  sortfunc=(sortfunc==ascendingType) ? descendingType : ascendingType;
  scan(TRUE);
  return 1;
  }
