defLonLatGrid(int nx, int ny, double c0, double lts, double re)
{
  int gridID;
  int nrx, nry, i;
  double c;
  double r0, s0;
  double r, s;
  double xla, phi;
  double *xvals, *yvals, *xbounds, *ybounds;

  get_grid_info(c0, re, &nrx, &nry, &r0, &s0, &c);

  if ( nx != nrx || ny != nry )
    {
      printf("nrx=%d nry=%d\n", nrx, nry);
      return(-1);
    }

  xvals = (double *) malloc(nx*sizeof(double));
  yvals = (double *) malloc(ny*sizeof(double));
  xbounds = (double *) malloc(nx*2*sizeof(double));
  ybounds = (double *) malloc(nx*2*sizeof(double));

  for ( i = 0; i < nx; ++i )
    {
      r = i+1;
      xla = det_lon_atovs(r, r0, lts, c, re);
      xvals[i] = xla;
      xla = det_lon_atovs(r-0.5, r0, lts, c, re);
      xbounds[2*i] = xla;
      xla = det_lon_atovs(r+0.5, r0, lts, c, re);
      xbounds[2*i+1] = xla;

    }

  for ( i = 0; i < ny; ++i )
    {
      s = (nry-i-1)+1;
      phi = det_lat_atovs(s, s0, lts, c, re);
      yvals[i] = phi;
      phi = det_lat_atovs(s-0.5, s0, lts, c, re);
      ybounds[2*i] = phi;
      phi = det_lat_atovs(s+0.5, s0, lts, c, re);
      ybounds[2*i+1] = phi;

    }

  gridID = gridCreate(GRID_LONLAT, nx*ny);
  gridDefXsize(gridID, nx);
  gridDefYsize(gridID, ny);
  gridDefXvals(gridID, xvals);
  gridDefYvals(gridID, yvals);


  free(xvals);
  free(yvals);
  free(xbounds);
  free(ybounds);

  return (gridID);
}
