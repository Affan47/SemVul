ComputeDepths()
{
  float *vector = this->ComputeProjectionVector();
  vtkIdType numcells = this->Input->GetNumberOfCells();

  float *center = this->CellCenters->GetPointer(0);
  float *depth = this->CellDepths->GetPointer(0);
  for (vtkIdType i = 0; i < numcells; i++)
    {
    *(depth++) = vtkMath::Dot(center, vector);
    center += 3;
    }
}
