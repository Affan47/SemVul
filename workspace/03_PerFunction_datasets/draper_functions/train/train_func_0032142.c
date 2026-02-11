DescribeDimensions(int ncFD,
                                                 const int *dimIds, int numDims)
{
  vtkStdString description;
  for (int i = 0; i < numDims; i++)
    {
    char name[NC_MAX_NAME+1];
    CALL_NETCDF(nc_inq_dimname(ncFD, dimIds[i], name));
    if (i > 0) description += " ";
    description += name;
    }
  return description;
}
