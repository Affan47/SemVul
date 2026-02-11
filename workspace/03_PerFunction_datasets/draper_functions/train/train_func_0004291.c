wrapGalleys(FXbool wrap){
  if(wrap && wrapGalleys()){
    options&=~DOCKSITE_NO_WRAP;
    recalc();
    }
  else if(!wrap && !wrapGalleys()){
    options|=DOCKSITE_NO_WRAP;
    recalc();
    }
  }
