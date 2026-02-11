xp(double x, double y) const {
  if(x== 1.) return xbp_  ;
  if(y==-1.) return xbp_  ;
  if(y== 1.) return xbp_/x;
  return (xbp_/sqrt(x))*sqrt((2.-(1.-x)*(1.-y))/(2.-(1.-x)*(1.+y)));
}
