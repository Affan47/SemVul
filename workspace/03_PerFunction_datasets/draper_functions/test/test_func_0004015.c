setItemData(FXFoldingItem* item,void* ptr) const {
  if(item==NULL){ fxerror("%s::setItemData: item is NULL.\n",getClassName()); }
  item->setData(ptr);
  }
