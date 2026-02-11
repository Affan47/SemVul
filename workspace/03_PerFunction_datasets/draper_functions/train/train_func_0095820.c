EvaluateInflation(double point[3])
{
  if (this->InflationImage == NULL) {
    return 1.0;
  }

  int ijk[3];
  double pcoords[3];
  double weights[8];
  int inBounds;
  int i;

  double inflation = 0.0;

  inBounds = this->InflationImage->ComputeStructuredCoordinates(point,ijk,pcoords);

  if (!inBounds)

    {
    vtkWarningMacro("Point out of extent.");
    return 0.0;
    }

  vtkCell* cell = this->InflationImage->GetCell(this->InflationImage->ComputeCellId(ijk));

  if (cell->GetCellType() == VTK_VOXEL)
  {
    vtkVoxel::InterpolationFunctions(pcoords,weights);
  }
  else if (cell->GetCellType() == VTK_PIXEL)
  {
    vtkPixel::InterpolationFunctions(pcoords,weights);
  }
  else
  {
    vtkErrorMacro("Non voxel or pixel cell found in PotentialImage");
    return 0.0;
  }

  int numberOfCellPoints = cell->GetNumberOfPoints();

  vtkDataArray* inflationArray = this->InflationImage->GetPointData()->GetScalars();

  for (i=0; i<numberOfCellPoints; i++)
  {
    double value = inflationArray->GetTuple1(cell->GetPointId(i));
    inflation += weights[i] * value;
  }

  return inflation - this->InflationThreshold;
}
