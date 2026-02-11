minmaxval(long nvals, double *array, int *imiss, double *minval, double *maxval)
{
  long i;
  double xmin =  DBL_MAX;
  double xmax = -DBL_MAX;

  if ( imiss )
    {
      for ( i = 0; i < nvals; i++ )
	{
	  if ( ! imiss[i] )
	    {
	      if      ( array[i] > xmax ) xmax = array[i];
	      else if ( array[i] < xmin ) xmin = array[i];
	    }
	}
    }
  else
    {
      for ( i = 0; i < nvals; i++ )
	{
	  if      ( array[i] > xmax ) xmax = array[i];
	  else if ( array[i] < xmin ) xmin = array[i];
	}
    }

  *minval = xmin;
  *maxval = xmax;
}
