farcdiv(field_t *field, double rconst)
{
  int i, len;
  int    grid     = field->grid;
  int    nmiss    = field->nmiss;
  double missval1 = field->missval;
  double missval2 = field->missval;
  double *array   = field->ptr;

  len    = gridInqSize(grid);

  if ( nmiss > 0 || IS_EQUAL(rconst, 0) )
    {
      for ( i = 0; i < len; i++ )
	array[i] = DIV(array[i], rconst);

      if ( IS_EQUAL(rconst, 0) ) field->nmiss = len;
    }
  else
    {
      for ( i = 0; i < len; i++ )
	array[i] /= rconst;
    }
}
