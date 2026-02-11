setIdColAcol() {

  double tmPrand = rndmPtr->flat();

  if (tmPrand < 0.33333333) {      setId( 21, 21, 11, -11); }
  else if (tmPrand < 0.66666667) { setId( 21, 21, 13, -13); }
  else {                            setId( 21, 21, 15, -15); }


  setColAcol( 1, 2, 2, 1, 0, 0, 0, 0);

}
