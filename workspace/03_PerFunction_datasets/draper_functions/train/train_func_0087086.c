LoadBoundsVariable(
                                                         int ncFD, int varId,
                                                         vtkDoubleArray *coords)
{
  int dimIds[3];
  CALL_NETCDF_GW(nc_inq_vardimid(ncFD, varId, dimIds));

  size_t dimSizes[3];
  for (int i = 0; i < 3; i++)
    {
    CALL_NETCDF_GW(nc_inq_dimlen(ncFD, dimIds[i], &dimSizes[i]));
    }

  if (dimSizes[2] != 4)
    {
    vtkGenericWarningMacro(<< "Expected 2D dependent coordinate bounds to have"
                           << " 4 entries in final dimension.  Instead has "
                           << dimSizes[2]);
    return 0;
    }


  std::vector<double> boundsData(dimSizes[0]*dimSizes[1]*4);
  CALL_NETCDF_GW(nc_get_var_double(ncFD, varId, &boundsData.at(0)));


  int numComponents = static_cast<int>(dimSizes[1]);
  vtkIdType numTuples = static_cast<vtkIdType>(dimSizes[0]);
  coords->SetNumberOfComponents(numComponents+1);
  coords->SetNumberOfTuples(numTuples+1);


  for (vtkIdType j = 0; j < numTuples; j++)
    {
    for (int i = 0; i < numComponents; i++)
      {
      coords->SetComponent(j, i, boundsData[(j*numComponents + i)*4 + 0]);
      }
    coords->SetComponent(j, numComponents,
                         boundsData[((j+1)*numComponents-1)*4 + 1]);
    }
  for (int i = 0; i < numComponents; i++)
    {
    coords->SetComponent(numTuples, i,
                         boundsData[((numTuples-1)*numComponents)*4 + 2]);
    }
  coords->SetComponent(numTuples, numComponents,
                       boundsData[(numTuples*numComponents-1)*4 + 3]);

  return 1;
}
