fxcheckXBM(FXStream& store){
  FXuchar signature[4];
  store.load(signature,4);
  store.position(-4,FXFromCurrent);
  return signature[0]=='#' && signature[1]=='d' && signature[2]=='e' && signature[3]=='f';
  }
