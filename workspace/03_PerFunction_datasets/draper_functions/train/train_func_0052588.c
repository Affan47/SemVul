DrawDotted (int x, int y, int tx, int ty, int active, int color)

{
  GdkGC *thegc;
  GdkPoint mypoints[100];
  int xlen, ylen, i;
  gint npoints ;
  int len;
  float step;

  xlen = tx - x;
  ylen = ty - y;

len=(int) rint(calc_vector(abs(xlen),abs(ylen))/6.3);
 step = 1./len;
npoints=len;
if (npoints>99)npoints=99;

  for (i = 0; i < npoints; i++)
    {
      mypoints[i].x = (gint16) ((x + i * step * xlen) * size_factor);
      mypoints[i].y = (gint16) ((y + i * step * ylen) * size_factor);
    }
  if (xbmflag)
  thegc= drawing_area->style->black_gc;
  else if (active)
  thegc=hlgc;
  else
  thegc=mygc[color];

    gdk_draw_points (picture, thegc,
		     (GdkPoint *) mypoints, (gint) npoints);
}
