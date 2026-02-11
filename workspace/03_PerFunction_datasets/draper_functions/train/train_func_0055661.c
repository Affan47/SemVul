gxnrev (gadouble x, gadouble y, gadouble *rlon, gadouble *rlat) {
gadouble rad,alpha;

  rad = hypot(x,y);
  alpha = 180.0*atan(rad)/pi;
  *rlat = 90.0 - 2.0*alpha;

  if (x==0.0 && y==0.0) *rlon = 0.0;
  else {
    *rlon = (180.0*atan2(y,x)/pi)-londif;
    while (*rlon < lonref-180.0) *rlon += 360.0;
    while (*rlon > lonref+180.0) *rlon -= 360.0;
  }
}
