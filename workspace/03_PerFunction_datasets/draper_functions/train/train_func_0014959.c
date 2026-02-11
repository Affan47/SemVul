ex_get_dimension_value(int exoid, int *var, int default_value, const char *dimension_name, int missing_ok)
{
  int status;
  char  errmsg[MAX_ERR_LENGTH];
  size_t idum;
  int dimid;

  if ((status = nc_inq_dimid( exoid, dimension_name, &dimid)) != NC_NOERR) {
    *var = default_value;
    if ( missing_ok ) {
      return (EX_NOERR);
    } else {
      exerrval = status;
      sprintf( errmsg,
         "Error: failed to retrieve dimension %s for file id %d",
         dimension_name, exoid);
      ex_err("ex_inquire",errmsg,exerrval);
      return (EX_FATAL);
    }
  }
  if ((status = nc_inq_dimlen( exoid, dimid, &idum)) != NC_NOERR) {
    *var = default_value;
    exerrval = status;
    sprintf( errmsg,
       "Error: failed to retrieve value for dimension %s for file id %d",
       dimension_name, exoid);
    ex_err("ex_inquire",errmsg,exerrval);
    return (EX_FATAL);
  }
  *var = (int)idum;
  return (EX_NOERR);
}
