position(FXint x,FXint y,FXint w,FXint h){
  FXint nr=nrows;
  FXint nc=ncols;
  if(w!=width || h!=height){
    getrowscols(nrows,ncols,w,h);
    if(nr!=nrows || nc!=ncols) update();
    }

  FXScrollArea::position(x,y,w,h);
  }
