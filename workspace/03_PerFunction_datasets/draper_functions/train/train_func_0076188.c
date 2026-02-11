setBounds(const FXRangef& r){


  center=r.center();


  diameter=r.longest();


  if(diameter<1.0E-30) diameter=1.0;


  scale=FXVec3f(1.0f,1.0f,1.0f);


  setDistance(1.1*diameter);

  return TRUE;
  }
