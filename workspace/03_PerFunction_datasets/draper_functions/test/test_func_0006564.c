zonmean(field_t field1, field_t *field2)
{
  long   i, j, nx, ny;
  int    rnmiss = 0;
  int    grid     = field1.grid;
  int    nmiss    = field1.nmiss;
  double missval1 = field1.missval;
  double missval2 = field1.missval;
  double *array   = field1.ptr;
  double rsum = 0, rsumw = 0, ravg = 0;

  nx    = gridInqXsize(grid);
  ny    = gridInqYsize(grid);

  for ( j = 0; j < ny; j++ )
    {
      rsum  = 0;
      rsumw = 0;
      if ( nmiss > 0 )
	{
	  for ( i = 0; i < nx; i++ )
	    if ( !DBL_IS_EQUAL(array[j*nx+i], missval1) )
	      {
		rsum  += array[j*nx+i];
		rsumw += 1;
	      }
	}
      else
	{
	  for ( i = 0; i < nx; i++ )
	    {
	      rsum  += array[j*nx+i];
	      rsumw += 1;
	    }
	}

      ravg = DIV(rsum, rsumw);

      if ( DBL_IS_EQUAL(ravg, missval1) ) rnmiss++;

      field2->ptr[j] = ravg;
    }

  field2->nmiss  = rnmiss;
}
