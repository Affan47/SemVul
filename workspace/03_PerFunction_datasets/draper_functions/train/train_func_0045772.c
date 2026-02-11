reset(FXbool forceclose){
  if (forceclose)
    close();
  else
    discard();

  clear();
  }
