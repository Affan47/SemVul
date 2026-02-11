setFont(FXFont* fnt){
  if(!fnt){ fxerror("%s::setFont: NULL font specified.\n",getClassName()); }
  if(font!=fnt){
    font=fnt;
    recalc();
    tabwidth=tabcolumns*font->getTextWidth(" ",1);
    barwidth=barcolumns*font->getTextWidth("8",1);

    recalc();
    update();
    }
  }
