setDecorations(FXuint decorations){
  FXuint opts=(options&~DECOR_ALL) | (decorations&DECOR_ALL);
  if(options!=opts){
    options=opts;
    if(xid) setdecorations();
    recalc();
    }
  }
