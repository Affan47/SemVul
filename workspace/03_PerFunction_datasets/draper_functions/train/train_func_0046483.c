unpack2scalar ( SV * arg, void * var, long n, int datatype ) {
  long data_length;

  if (datatype == TSTRING)
    croak("unpack2scalar() - how did you manage to call me with a TSTRING datatype?!");

  data_length = n * sizeof_datatype(datatype);

  SvGROW(arg, data_length);
  memcpy(SvPV(arg,PL_na), var, data_length);

  return;
}
