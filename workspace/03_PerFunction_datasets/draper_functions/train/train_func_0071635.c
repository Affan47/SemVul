EvaluateForce(double point[3], double force[3], bool normalize)
{
  int ijk[3];
  double pcoords[3];
  double weights[8];
  int inBounds;
  int i;

  force[0] = force[1] = force[2] = 0.0;

  inBounds = this->PotentialGradientImage->ComputeStructuredCoordinates(point,ijk,pcoords);

  if (!inBounds)
    {

    return;
    }

  vtkCell* cell = this->PotentialGradientImage->GetCell(this->PotentialGradientImage->ComputeCellId(ijk));

  if (cell->GetCellType() == VTK_VOXEL)
  {
    vtkVoxel::InterpolationFunctions(pcoords,weights);
  }
  else
  {
    vtkErrorMacro("Non voxel cell found in PotentialImage");
  }

  int numberOfCellPoints = cell->GetNumberOfPoints();

  vtkDataArray* gradientVectorsArray = this->PotentialGradientImage->GetPointData()->GetScalars();

  for (i=0; i<numberOfCellPoints; i++)
  {
    double vectorValue[3];
    gradientVectorsArray->GetTuple(cell->GetPointId(i),vectorValue);
    force[0] += weights[i] * vectorValue[0];
    force[1] += weights[i] * vectorValue[1];
    force[2] += weights[i] * vectorValue[2];
  }

  if (normalize && this->PotentialMaxNorm > VTK_VMTK_DOUBLE_TOL)
  {
    force[0] /= this->PotentialMaxNorm;
    force[1] /= this->PotentialMaxNorm;
    force[2] /= this->PotentialMaxNorm;
  }

  force[0] *= -1.0;
  force[1] *= -1.0;
  force[2] *= -1.0;
}
