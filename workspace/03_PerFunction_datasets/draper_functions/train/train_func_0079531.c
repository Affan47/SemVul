GetCell(vtkIdType cellId)
{
  vtkCell *cell = NULL;
  int numPts = 1<<this->GetDimension();
  int ptIdx;
  double x[3];

  switch (this->GetDimension())
    {
    case 1:
      cell = this->Line;

      break;

    case 2:
      cell = this->Pixel;
      break;

    case 3:
      cell = this->Voxel;
      break;
    }

  if (this->DualGridFlag)
    {
    vtkIdTypeArray* cornerLeafIds = this->GetCornerLeafIds();
    assert("Index out of bounds." &&
           cellId >= 0 && cellId < cornerLeafIds->GetNumberOfTuples());
    vtkPoints* leafCenters = this->GetLeafCenters();
    vtkIdType* ptr = cornerLeafIds->GetPointer(0) + cellId*numPts;
    for (ptIdx = 0; ptIdx < numPts; ++ptIdx)
      {
      cell->PointIds->SetId(ptIdx, *ptr);
      leafCenters->GetPoint(*ptr, x);
      cell->Points->SetPoint(ptIdx,x);
      ++ptr;
      }
    }
  else
    {
    vtkIdTypeArray* leafCornerIds = this->GetLeafCornerIds();
    assert("Index out of bounds." &&
           cellId >= 0 && cellId < leafCornerIds->GetNumberOfTuples());
    vtkPoints* cornerPoints = this->GetCornerPoints();
    vtkIdType* ptr = leafCornerIds->GetPointer(0) + cellId*numPts;
    for (ptIdx = 0; ptIdx < numPts; ++ptIdx)
      {
      cell->PointIds->SetId(ptIdx, *ptr);
      cornerPoints->GetPoint(*ptr, x);
      cell->Points->SetPoint(ptIdx,x);
      ++ptr;
      }
    }

  return cell;
}
