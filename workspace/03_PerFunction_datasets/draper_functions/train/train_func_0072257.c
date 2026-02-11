rotozoomSurfaceSizeTrig(int width, int height, double angle, double zoom, int *dstwidth, int *dstheight,
			     double *canglezoom, double *sanglezoom)
{
  double x, y, cx, cy, sx, sy;
  double radangle;
  int dstwidthhalf, dstheighthalf;


    radangle = angle * (M_PI / 180.0);
    *sanglezoom = sin(radangle);
    *canglezoom = cos(radangle);
    *sanglezoom *= zoom;
    *canglezoom *= zoom;
    x = width / 2;
    y = height / 2;
    cx = *canglezoom * x;
    cy = *canglezoom * y;
    sx = *sanglezoom * x;
    sy = *sanglezoom * y;
    dstwidthhalf = MAX((int)
		       ceil(MAX(MAX(MAX(fabs(cx + sy), fabs(cx - sy)), fabs(-cx + sy)), fabs(-cx - sy))), 1);
    dstheighthalf = MAX((int)
			ceil(MAX(MAX(MAX(fabs(sx + cy), fabs(sx - cy)), fabs(-sx + cy)), fabs(-sx - cy))), 1);
    *dstwidth = 2 * dstwidthhalf;
    *dstheight = 2 * dstheighthalf;
}
