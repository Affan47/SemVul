farexpr(field_t *field1, field_t field2, field_t field3, double (*expression)(double, double, double, double))
{
  int   i, len;
  const int     grid1    = field1->grid;
  const int     nmiss1   = field1->nmiss;
  const double  missval1 = field1->missval;
  double       *array1   = field1->ptr;
  const int     grid2    = field2.grid;
  const int     nmiss2   = field2.nmiss;
  const double  missval2 = field2.missval;
  const double *array2   = field2.ptr;
  const int     grid3    = field3.grid;
  const int     nmiss3   = field3.nmiss;
  const double  missval3 = field3.missval;
  const double *array3   = field3.ptr;

  len = gridInqSize(grid1);

  if ( len != gridInqSize(grid2) || len != gridInqSize(grid3) )
    cdoAbort("Fields have different gridsize (%s)", __func__);

  if ( nmiss1 > 0 || nmiss2 > 0 || nmiss3 > 0 )
    {
      for ( i = 0; i < len; i++ )
        if ( DBL_IS_EQUAL(array1[i], missval1) || DBL_IS_EQUAL(array2[i], missval2) || DBL_IS_EQUAL(array3[i], missval3))
	  array1[i] = missval1;
	else
	  array1[i] = expression(array1[i], array2[i], array3[i], missval1);
    }
  else
    {
      for ( i = 0; i < len; i++ )
        array1[i] = expression(array1[i], array2[i], array3[i], missval1);
    }

  field1->nmiss = 0;
  for ( i = 0; i < len; i++ )
    if ( DBL_IS_EQUAL(array1[i], missval1) ) field1->nmiss++;
}
