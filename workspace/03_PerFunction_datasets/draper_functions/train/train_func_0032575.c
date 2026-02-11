define_grid(dsets_t *pfi)
{
  int gridID, gridtype;
  int nx, ny;
  double *xvals, *yvals;
  int lgauss = FALSE;

  nx = pfi->dnum[0];
  ny = pfi->dnum[1];

  xvals = (double *) malloc(nx*sizeof(double));
  yvals = (double *) malloc(ny*sizeof(double));

  get_dim_vals(pfi, xvals, nx, 0);
  get_dim_vals(pfi, yvals, ny, 1);

  if ( pfi->yrflg ) rev_vals(yvals, ny);

  if ( pfi->linear[1] == 0 ) lgauss = y_is_gauss(yvals, ny);

  if ( lgauss ) gridtype = GRID_GAUSSIAN;
  else          gridtype = GRID_LONLAT;

  gridID = gridCreate(gridtype, nx*ny);
  gridDefXsize(gridID, nx);
  gridDefYsize(gridID, ny);

  gridDefXvals(gridID, xvals);
  gridDefYvals(gridID, yvals);

  free(xvals);
  free(yvals);

  return (gridID);
}
