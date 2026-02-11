loadPixels(FXStream & store){
  if(options&CURSOR_OWNED){FXFREE(&data);}
  if(fxloadICO(store,data,width,height,hotx,hoty)){
    options|=CURSOR_OWNED;
    return true;
    }
  return false;
  }
