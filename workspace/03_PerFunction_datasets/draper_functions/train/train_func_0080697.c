clip( int *x, int *y, int *w, int *h, int image_width, int image_height )
{
  if ( *x < 0 ) { *w += *x; *x=0; }
  if ( *y < 0 ) { *h += *y; *y=0; }
  if ( *w > image_width - *x ) *w = image_width - *x;
  if ( *h > image_height - *y ) *h = image_height - *y;
}
