isItemCurrent(FXint index) const {
  if(index<0 || items.no()<=index){ fxerror("%s::isItemCurrent: index out of range.\n",getClassName()); }
  return index==current;
  }
