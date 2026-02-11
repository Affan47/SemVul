save(FXStream& store) const {
  FXint num=no();
  store << num;
  for(FXint i=0; i<num; i++){
    store << ptr[i];
    }
  }
