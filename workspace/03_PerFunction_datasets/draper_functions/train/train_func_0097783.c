gxconv (gadouble s, gadouble t, gadouble *x, gadouble *y, gaint level) {

  if (level>2 && gconv!=NULL) (*gconv)(s,t,&s,&t);
  if (level>1 && fconv!=0) (*fconv)(s,t,&s,&t);
  if (level>0) {
    s=s*xm+xb;
    t=t*ym+yb;
  }
  *x=s;
  *y=t;
}
