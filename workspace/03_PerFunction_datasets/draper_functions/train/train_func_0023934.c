gxdrec (gadouble x1, gadouble x2, gadouble y1, gadouble y2) {
gaint i1,i2,j1,j2;

  i1 = (gaint)(x1*xscl+0.5);
  j1 = height - (gaint)(y1*yscl+0.5);
  i2 = (gaint)(x2*xscl+0.5);
  j2 = height - (gaint)(y2*yscl+0.5);
  if (i1!=i2 && j1!=j2) {
    XFillRectangle (display, drwbl, gc, i1, j2, i2-i1, j1-j2);
  } else {
    XDrawLine (display, drwbl, gc, i1, j1, i2, j2);
  }
  if (QLength(display)&&rstate) gxdeve(0);
}
