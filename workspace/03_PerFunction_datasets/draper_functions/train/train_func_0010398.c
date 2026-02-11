IsTimeDimension(int ncFD, int dimId)
{
  char name[NC_MAX_NAME+1];
  CALL_NETCDF(nc_inq_dimname(ncFD, dimId, name));
  name[4] = '\0';
  return (vtksys::SystemTools::Strucmp(name, "time") == 0);
}
