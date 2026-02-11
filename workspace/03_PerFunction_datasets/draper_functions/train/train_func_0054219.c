setSelTextColor(FXColor clr){
  if(clr!=seltextColor){
    seltextColor=clr;
    updateRange(selstartpos,selendpos);
    }
  }
