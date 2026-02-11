gaarrw (gadouble x, gadouble y, gadouble ang, gadouble siz, gadouble asiz) {
gadouble xx,yy;

  if (siz<0.0001) {
    gxmark (2, x, y, 0.01);
    return;
  }
  gxplot (x,y,3);
  xx = x+siz*cos(ang);
  yy = y+siz*sin(ang);
  gxplot (xx,yy,2);
  if (asiz==0.0) return;
  if (asiz<0.0) asiz = -1.0*asiz*siz;
  gxplot (xx+asiz*cos(ang+a150),yy+asiz*sin(ang+a150),2);
  gxplot (xx,yy,3);
  gxplot (xx+asiz*cos(ang-a150),yy+asiz*sin(ang-a150),2);
}
