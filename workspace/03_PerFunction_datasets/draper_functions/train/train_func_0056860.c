gridInqXinc(int gridID)
{
  double xinc;
  grid_t *gridptr;

  gridptr = ( grid_t *) reshGetVal ( gridID, &gridOps );

  grid_check_ptr(gridID, gridptr);

  xinc = gridptr->xinc;

  if ( (! (fabs(xinc) > 0)) && gridptr->xvals )
    {
      int xsize;
      double *xvals;

      xsize = gridptr->xsize;
      xvals = gridptr->xvals;

      if ( xsize > 1 )
        {
          long i;
          xinc = fabs(xvals[xsize-1] - xvals[0])/(xsize-1);
          for ( i = 2; i < xsize; i++ )
            if ( fabs(fabs(xvals[i-1] - xvals[i]) - xinc) > 0.01*xinc ) break;

          if ( i < xsize ) xinc = 0;
        }
    }

  return (xinc);
}
