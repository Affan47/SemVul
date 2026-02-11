onUpdRGBText(FXObject*,FXSelector sel,void*){
  FXint which=FXSELID(sel)-ID_RGB_RED_TEXT;
  rgbatext[which]->setText(FXStringVal(255.0f*rgba[which],1,FALSE));
  return 1;
  }
