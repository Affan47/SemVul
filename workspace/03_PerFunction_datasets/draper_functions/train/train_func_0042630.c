Add2DSphericalCoordinates(vtkPoints *points,
                                                  const int extent[6])
{
  points->SetDataTypeToDouble();
  points->Allocate(  (extent[1]-extent[0]+1)
                   * (extent[3]-extent[2]+1)
                   * (extent[5]-extent[4]+1) );

  vtkDependentDimensionInfo *info
    = this->FindDependentDimensionInfo(this->LoadingDimensions);

  vtkDoubleArray *longitudeCoordinates = info->GetLongitudeCoordinates();
  vtkDoubleArray *latitudeCoordinates = info->GetLatitudeCoordinates();

  vtkDoubleArray *verticalCoordinates = NULL;
  if (this->LoadingDimensions->GetNumberOfTuples() == 3)
    {
    int vertDim = this->LoadingDimensions->GetValue(0);
    if (info->GetHasBounds())
      {
      verticalCoordinates = this->GetDimensionInfo(vertDim)->GetBounds();
      }
    else
      {
      verticalCoordinates = this->GetDimensionInfo(vertDim)->GetCoordinates();
      }
    }


  double vertScale = this->VerticalScale;
  double vertBias = this->VerticalBias;
  if (verticalCoordinates)
    {
    double *verticalRange = verticalCoordinates->GetRange();
    if (   (verticalRange[0]*vertScale + vertBias < 0)
        || (verticalRange[1]*vertScale + vertBias < 0) )
      {
      vertBias = -std::min(verticalRange[0], verticalRange[1])*vertScale;
      }
    }
  else
    {
    if (vertScale + vertBias <= 0)
      {
      vertScale = 1.0;
      vertBias = 0.0;
      }
    }

  for (int k = extent[4]; k <= extent[5]; k++)
    {
    double h;
    if (verticalCoordinates)
      {
      h = verticalCoordinates->GetValue(k)*vertScale + vertBias;
      }
    else
      {
      h = vertScale + vertBias;
      }
    for (int j = extent[2]; j <= extent[3]; j++)
      {
      for (int i = extent[0]; i <= extent[1]; i++)
        {
        double lon = longitudeCoordinates->GetComponent(j, i);
        double lat = latitudeCoordinates->GetComponent(j, i);
        lon = vtkMath::RadiansFromDegrees(lon);
        lat = vtkMath::RadiansFromDegrees(lat);

        double cartesianCoord[3];
        cartesianCoord[0] = h*cos(lon)*cos(lat);
        cartesianCoord[1] = h*sin(lon)*cos(lat);
        cartesianCoord[2] = h*sin(lat);
        points->InsertNextPoint(cartesianCoord);
        }
      }
    }
}
