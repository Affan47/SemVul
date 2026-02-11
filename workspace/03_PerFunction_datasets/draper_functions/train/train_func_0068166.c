setmissval(long nvals, int *imiss, double missval, double *array)
{
  long i;

  if ( imiss )
    {
      for ( i = 0; i < nvals; ++i )
	if ( imiss[i] ) array[i] = missval;
    }
}
