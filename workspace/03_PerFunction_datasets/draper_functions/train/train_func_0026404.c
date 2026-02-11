onTimeout(FXObject*,FXSelector,void*){


  if(closing<0) return 0;


  closingHeight-=heightIncrement;
  heightIncrement+=5;


  recalc();


  if(closingHeight>0){
    getApp()->addTimeout(this,ID_SHUTTER_TIMEOUT,getApp()->getAnimSpeed());
    return 1;
    }


  closing=-1;

  return 1;
  }
