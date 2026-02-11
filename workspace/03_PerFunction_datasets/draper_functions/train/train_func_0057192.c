setViewWidth( float w ) {
  if( w > 1.0 ) view_width = 1.0;
  else if( w <= 0.0 ) view_width = 0.001;
  else view_width = w;
}
