imlinei(GFilt g, int rno, int sno, int flag, int type,
	     double x, double y,
	     double x1, double y1, double x2, double y2)
{
  double vx[2];
  double vy[2];
  int xval, yval;
  double invslope, xoffset;


  if( 0 ){
    rno = rno;
    x = x;
    y = y;
  }


  x1 = (x1 - g->xmin)/g->block + 1.0;
  y1 = (y1 - g->ymin)/g->block + 1.0;
  x2 = (x2 - g->xmin)/g->block + 1.0;
  y2 = (y2 - g->ymin)/g->block + 1.0;

  if( y1 < y2 ){
    vx[0] = x1;
    vy[0] = y1;
    vx[1] = x2;
    vy[1] = y2;
  }
  else{
    vx[0] = x2;
    vy[0] = y2;
    vx[1] = x1;
    vy[1] = y1;
  }

  g->shapes[sno].ystart = PIXNUM(vy[0]);
  g->shapes[sno].ystop = PIXNUM(vy[1]);
  g->shapes[sno].scanlist = (Scan *)calloc(g->y1+1, sizeof(Scan));
  marky(g, sno, flag, type);
  if( feq(vy[0],vy[1]) ){
    rgs_mark(g, g->shapes[sno].scanlist, sno, flag, type,
	     (int)min(vx[0],vx[1]), (int)vy[0]);
    rgs_mark(g, g->shapes[sno].scanlist, sno, flag, type,
	     (int)max(vx[0],vx[1]), (int)vy[0]);
  }
  else{

    invslope = (vx[0] - vx[1]) / (vy[0] - vy[1]);
    xoffset = vx[0];
    for(yval=vy[0]; yval<=vy[1]; yval++){
      xval = xoffset;
      rgs_mark(g, g->shapes[sno].scanlist, sno, flag, type, xval, yval);
      xoffset = xoffset + invslope;
    }
  }
}
