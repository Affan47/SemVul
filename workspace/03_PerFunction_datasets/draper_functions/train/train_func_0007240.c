setAnchorItem(FXint index){
  if(index<-1 || items.no()<=index){ fxerror("%s::setAnchorItem: index out of range.\n",getClassName()); }
  anchor=index;
  extent=index;
  }
