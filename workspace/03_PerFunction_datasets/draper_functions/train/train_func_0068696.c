setSat(FXfloat s){
  s=FXCLAMP(0.0f,s,1.0f);
  if(hsv[1]!=s){
    hsv[1]=s;
    update(satvalx-4,satvaly-4,9,9);
    satValToXY(satvalx,satvaly,hsv[1],hsv[2]);
    update(satvalx-4,satvaly-4,9,9);
    }
  }
