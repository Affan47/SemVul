Wconv1(v,ker)
double v;
INT ker;
{ double v2;
  v = fabs(v);
  switch(ker)
  { case WGAUS: return(-0.5*SQRPI*GFACT*exp(-SQR(GFACT*v)/4));
    case WRECT:
      if (v>2) return(0.0);
      return(1.0);
    case WEPAN:
      if (v>2) return(0.0);
      return((-16+v*(12-v*v))/6);
    case WBISQ:
      if (v>2) return(0.0);
      v2 = 2-v;
      return(-v2*v2*v2*v2*(32+v*(64+v*(24+v*3)))/210);
  }
  ERROR(("Wconv1 not implemented for kernel %d",ker));
  return(0.0);
}
