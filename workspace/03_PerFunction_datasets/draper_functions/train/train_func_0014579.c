getDefaultWidth(){
  register FXint w=KNOBSIZE;
  if(options&KNOB_TICKS) w+=4;
  return w+padleft+padright+(border<<1);
  }
