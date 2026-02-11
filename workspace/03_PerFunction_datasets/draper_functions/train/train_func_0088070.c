doinit() {

  for(long ix=1000001;ix<1000007;++ix) {
    addToList(21,21,ix,-ix);
  }

  for(long ix=2000001;ix<2000007;++ix) {
    addToList(21,21,ix,-ix);
  }
  orderInGs(2);
  orderInGem(0);
  VVSSVertex::doinit();
}
