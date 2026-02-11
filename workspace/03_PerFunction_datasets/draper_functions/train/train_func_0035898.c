getDefaultHeight(){
  FXint th=0,ih=0,h;
  if(!label.empty()){
    th=labelHeight(label);
    }
  if(icon){
    ih=icon->getHeight();
    }
  if(!(options&(ICON_ABOVE_TEXT|ICON_BELOW_TEXT))) h=FXMAX(th,ih); else h=th+ih;
  return h+padtop+padbottom+(border<<1);
  }
