cdfInqDatatype(int xtype, int lunsigned)
{
  int datatype = -1;

#if  defined  (HAVE_NETCDF4)
  if ( xtype == NC_BYTE && lunsigned ) xtype = NC_UBYTE;
#endif

  if      ( xtype == NC_BYTE   )  datatype = DATATYPE_INT8;

  else if ( xtype == NC_SHORT  )  datatype = DATATYPE_INT16;
  else if ( xtype == NC_INT    )  datatype = DATATYPE_INT32;
  else if ( xtype == NC_FLOAT  )  datatype = DATATYPE_FLT32;
  else if ( xtype == NC_DOUBLE )  datatype = DATATYPE_FLT64;
#if  defined  (HAVE_NETCDF4)
  else if ( xtype == NC_UBYTE  )  datatype = DATATYPE_UINT8;
  else if ( xtype == NC_LONG   )  datatype = DATATYPE_INT32;
  else if ( xtype == NC_USHORT )  datatype = DATATYPE_UINT16;
  else if ( xtype == NC_UINT   )  datatype = DATATYPE_UINT32;
  else if ( xtype == NC_INT64  )  datatype = DATATYPE_FLT64;
  else if ( xtype == NC_UINT64 )  datatype = DATATYPE_FLT64;
#endif

  return (datatype);
}
