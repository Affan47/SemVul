ExecuteInformation()
{

  if (this->ReadMINCFileAttributes() == 0)
    {
    return;
    }


  int dataExtent[6];
  dataExtent[0] = dataExtent[1] = 0;
  dataExtent[2] = dataExtent[3] = 0;
  dataExtent[4] = dataExtent[5] = 0;

  double dataSpacing[3];
  dataSpacing[0] = dataSpacing[1] = dataSpacing[2] = 1.0;

  double dataOrigin[3];
  dataOrigin[0] = dataOrigin[1] = dataOrigin[2] = 0.0;

  int numberOfComponents = 1;

  int fileType = this->ConvertMINCTypeToVTKType(this->MINCImageType,
                                                this->MINCImageTypeSigned);

  if (fileType == 0)
    {
    vtkErrorMacro("Couldn't convert NetCDF data type " << this->MINCImageType
                  << (this->MINCImageTypeSigned ? " signed" : " unsigned")
                  << " to a VTK data type.");
    return;
    }


  this->FindRangeAndRescaleValues();


  int dataType = fileType;
  if (this->RescaleRealValues &&
      this->ImageAttributes->GetImageMin() &&
      this->ImageAttributes->GetImageMax())
    {
    switch (fileType)
      {
      case VTK_SIGNED_CHAR:
      case VTK_UNSIGNED_CHAR:
      case VTK_CHAR:
      case VTK_SHORT:
      case VTK_UNSIGNED_SHORT:
        dataType = VTK_FLOAT;
        break;
      case VTK_INT:
      case VTK_UNSIGNED_INT:
        dataType = VTK_DOUBLE;
        break;
      default:
        dataType = fileType;
        break;
      }
    }


  vtkStringArray *dimensionNames =
    this->ImageAttributes->GetDimensionNames();
  vtkIdTypeArray *dimensionLengths =
    this->ImageAttributes->GetDimensionLengths();

  int numberOfDimensions = dimensionNames->GetNumberOfValues();
  for (int i = 0; i < numberOfDimensions; i++)
    {
    const char *dimName = dimensionNames->GetValue(i);
    vtkIdType dimLength = dimensionLengths->GetValue(i);


    int dimIndex = this->IndexFromDimensionName(dimName);


    if (dimIndex >= 0 && dimIndex < 3)
      {

      double step = this->ImageAttributes->GetAttributeValueAsDouble(
        dimName, MIstep);
      if (step)
        {
        dataSpacing[dimIndex] = step;
        }


      double start = this->ImageAttributes->GetAttributeValueAsDouble(
        dimName, MIstart);
      if (start)
        {
        dataOrigin[dimIndex] = start;
        }


      dataExtent[2*dimIndex + 1] = static_cast<int>(dimLength - 1);
      }


    else if (strcmp(dimName, MIvector_dimension) == 0)
      {
      numberOfComponents = dimLength;
      }
    }

  this->SetDataExtent(dataExtent);
  this->SetDataSpacing(dataSpacing[0], dataSpacing[1], dataSpacing[2]);
  this->SetDataOrigin(dataOrigin[0], dataOrigin[1], dataOrigin[2]);
  this->SetDataScalarType(dataType);
  this->SetNumberOfScalarComponents(numberOfComponents);
}
