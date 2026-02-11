alpha(int x,int y) {
  rgbptr a;
  if (!alphamask) return 0;
  a=alphamask+(y*(isrc->W)+x);
  return( (int)(a[0]) );
}
