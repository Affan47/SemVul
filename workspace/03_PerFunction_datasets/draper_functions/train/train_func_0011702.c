cdf_inq_nvars(int ncid, int *nvarsp)
{
  int status;

  status = nc_inq_nvars(ncid, nvarsp);

  if ( CDF_Debug || status != NC_NOERR )
    Message("ncid = %d  nvars = %d", ncid, *nvarsp);

  if ( status != NC_NOERR ) Error("%s", nc_strerror(status));
}
