movespot(FXint x,FXint y){
  if(spotx!=x || spoty!=y){
    update(dialx+spotx-4,dialy+spoty-4,9,9);
    xytohs(hsv[0],hsv[1],x,y);
    hstoxy(spotx,spoty,hsv[0],hsv[1]);
    update(dialx+spotx-4,dialy+spoty-4,9,9);
    }
  }
