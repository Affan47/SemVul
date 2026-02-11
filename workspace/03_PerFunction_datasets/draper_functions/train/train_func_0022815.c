fldunm(field_t *field)
{
  size_t i;

  field->nmiss = 0;
  for ( i = 0; i < field->size; i++ )
    if ( DBL_IS_EQUAL(field->ptr[i], field->missval) ) field->nmiss++;
}
