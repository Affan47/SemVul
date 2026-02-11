factorizationScale() const {

  if ( theUserScale != ZERO )
    return sqr(theUserScale);

  return lastSHat();

}
