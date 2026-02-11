correct_xvals(long nlon, long inc, double *xvals)
{
  long i;

  if ( IS_EQUAL(xvals[0], xvals[(nlon-1)*inc]) ) xvals[(nlon-1)*inc] += 360;

  if ( xvals[0] > xvals[(nlon-1)*inc] )
    for ( i = 0; i < nlon; i++ )
      if ( xvals[i*inc] >= 180 ) xvals[i*inc] -= 360;

  for ( i = 0; i < nlon; i++ )
    {
      if ( xvals[i*inc] < -180 ) xvals[i*inc] += 360;
      if ( xvals[i*inc] >  360 ) xvals[i*inc] -= 360;
    }

  if ( xvals[0] > xvals[(nlon-1)*inc] )
    for ( i = 1; i < nlon; i++ )
      if ( xvals[i*inc] < xvals[(i-1)*inc] ) xvals[i*inc] += 360;
}
