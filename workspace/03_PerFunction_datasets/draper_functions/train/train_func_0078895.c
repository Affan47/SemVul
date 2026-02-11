GetNumberOfElementsFromArray(const char *array, unsigned int length)
{
  unsigned int c=0;
  if( !length || !array ) return 0;
  const char *parray = array;
  const char *end = array + length;
  bool valuefound = false;
  for(; parray != end; ++parray)
    {
    if( *parray == ' ' )
      {

      }
    else if( *parray == '\\' )
      {
      if( valuefound )
        {
        ++c;
        valuefound = false;
        }
      }
    else
      {
      valuefound = true;
      }
    }
  if( valuefound ) ++c;
  return c;
}
