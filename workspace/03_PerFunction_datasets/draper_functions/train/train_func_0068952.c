create(){
  FXFrame::create();
  if(!colorType){colorType=getApp()->registerDragType(colorTypeName);}
  updatebar();
  bar->create();
  }
