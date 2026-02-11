DrawDashedWedge (int x, int y, int tx, int ty, int active,int color)

{
  int i, xlen, ylen;
  GdkGC *thegc;
  int len;
  float step,factor;

  if (xbmflag)
  thegc = drawing_area->style->black_gc;
  else if (active)
    thegc = hlgc;
  else
  thegc= mygc[color];

  xlen = tx - x;
  ylen = ty - y;

len=(int) rint(calc_vector(abs(xlen),abs(ylen))/8.);
if (len<8) len=8;
 step = 1./len;
 factor=0.0125;
 if (len>20) factor= 0.00125;
 if (len==8) {
   factor =0.03;
 }
  for (i = 1; i < len; i++)
    gdk_draw_line (picture, thegc,
		   (x + step * i * xlen - factor * ylen * i) * size_factor,
		   (y + step * i * ylen + factor * xlen * i) * size_factor,
		   (x + step * i * xlen + factor * ylen * i) * size_factor,
		   (y + step * i * ylen - factor * xlen * i) * size_factor);
}
