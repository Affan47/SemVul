clamp(float x, float min, float max) {
  if( x < min )
    x = min;
  else if( x > max )
    x = max;
  return x;
}
