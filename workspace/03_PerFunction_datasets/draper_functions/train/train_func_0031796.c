extInqDatatype(int prec, int number)
{
  int datatype;

  if ( number == 2 )
    {
      if ( prec == DOUBLE_PRECISION ) datatype = DATATYPE_CPX64;
      else                            datatype = DATATYPE_CPX32;
    }
  else
    {
      if ( prec == DOUBLE_PRECISION ) datatype = DATATYPE_FLT64;
      else                            datatype = DATATYPE_FLT32;
    }

  return (datatype);
}
