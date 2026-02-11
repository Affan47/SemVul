setAngle(FXint ang){
  if(xid){ fxerror("%s::setAngle: font has already been created.\n",getClassName()); }
  angle=(ang+34560)%23040-11520;
  if(angle!=ang){
    angle=ang;
    }
  }
