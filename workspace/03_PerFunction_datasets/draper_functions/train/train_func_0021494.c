killFocus(){
  if(getFocus()) getFocus()->killFocus();
  flags&=~FLAG_HELP;
  flags|=FLAG_UPDATE;
  }
