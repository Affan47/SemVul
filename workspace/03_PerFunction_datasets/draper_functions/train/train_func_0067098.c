onCmdCMYText(FXObject*,FXSelector sel,void*){
  FXint which=FXSELID(sel)-ID_CMY_CYAN_TEXT;
  FXfloat val=0.003921568627f*FXFloatVal(cmytext[which]->getText());
  rgba[which]=1.0f-val;
  fxrgb_to_hsv(hsva[0],hsva[1],hsva[2],rgba[0],rgba[1],rgba[2]);
  hsva[3]=rgba[3];
  updateWell();
  if(target) target->tryHandle(this,FXSEL(SEL_COMMAND,message),(void*)(FXuval)well->getRGBA());
  return 1;
  }
