clampr(float *x, float min, float max) {
  bool ret = false;
  if( *x < min ) {
    *x = min;
    ret = true;
  } else if( *x > max ) {
    *x = max;
    ret = true;
  }
  return ret;
}
