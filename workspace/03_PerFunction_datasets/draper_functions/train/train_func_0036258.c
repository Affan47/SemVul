compare (const Hep3Vector & v) const {
  if       ( dz > v.dz ) {
    return 1;
  } else if ( dz < v.dz ) {
    return -1;
  } else if ( dy > v.dy ) {
    return 1;
  } else if ( dy < v.dy ) {
    return -1;
  } else if ( dx > v.dx ) {
    return 1;
  } else if ( dx < v.dx ) {
    return -1;
  } else {
    return 0;
  }
}
