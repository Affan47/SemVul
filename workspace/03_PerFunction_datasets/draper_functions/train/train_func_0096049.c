onRefreshTimer(FXObject*,FXSelector,void*){
  if(flags&FLAG_UPDATE){
    scan(FALSE);
    counter=(counter+1)%REFRESHFREQUENCY;
    }
  getApp()->addTimeout(this,ID_REFRESHTIMER,REFRESHINTERVAL);
  return 0;
  }
