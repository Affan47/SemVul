Wconv5(v,ker)
double v;
INT ker;
{ double gv;
  switch(ker)
  { case WGAUS:
      gv = GFACT*v;
      return(-exp(-SQR(gv)/4)*GFACT*GFACT*GFACT*GFACT*gv*(60-gv*gv*(20-gv*gv))*SQRPI/32);
  }
  ERROR(("Wconv5 not implemented for kernel %d",ker));
  return(0.0);
}
