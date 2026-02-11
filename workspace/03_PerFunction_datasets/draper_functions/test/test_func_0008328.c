onUpdHeader(FXObject*,FXSelector,void*){
  header->setArrowDir(0,(sortfunc==ascending || sortfunc==ascendingCase)  ? FALSE : (sortfunc==descending || sortfunc==descendingCase) ? TRUE : MAYBE);
  header->setArrowDir(1,(sortfunc==ascendingType)  ? FALSE : (sortfunc==descendingType) ? TRUE : MAYBE);
  header->setArrowDir(2,(sortfunc==ascendingSize)  ? FALSE : (sortfunc==descendingSize) ? TRUE : MAYBE);
  header->setArrowDir(3,(sortfunc==ascendingTime)  ? FALSE : (sortfunc==descendingTime) ? TRUE : MAYBE);
  header->setArrowDir(4,(sortfunc==ascendingUser)  ? FALSE : (sortfunc==descendingUser) ? TRUE : MAYBE);
  header->setArrowDir(5,(sortfunc==ascendingGroup) ? FALSE : (sortfunc==descendingGroup)? TRUE : MAYBE);
  return 1;
  }
