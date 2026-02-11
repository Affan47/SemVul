phi() const {
  if ( d == 0 ) {
    return 0;
  } else if ( (d < 0) || (d == CLHEP::pi) )  {
    return +CLHEP::halfpi;
  } else {
    return -CLHEP::halfpi;
  }
}
