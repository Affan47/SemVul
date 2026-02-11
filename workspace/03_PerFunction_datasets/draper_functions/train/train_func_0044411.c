onCmdGradientBackColor(FXObject*,FXSelector sel,void* ptr){
  FXColor color=(FXColor)(FXuval)ptr;
  background[FXSELID(sel)-ID_TOP_COLOR]=color;
  if(FXSELTYPE(sel)==SEL_COMMAND || !turbomode){
    update();
    }
  return 1;
  }
