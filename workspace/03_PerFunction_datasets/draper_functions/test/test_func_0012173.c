setCellColor(FXint r,FXint c,FXColor clr){
  if(clr!=cellBackColor[r&1][c&1]){
    cellBackColor[r&1][c&1]=clr;
    update();
    }
  }
