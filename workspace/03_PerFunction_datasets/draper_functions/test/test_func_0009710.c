RemoveDeletedCells()
{
  if(this->ThresholdGrid)
    {
    this->ThresholdGrid->Delete();
    }
  this->ThresholdGrid = vtkUnstructuredGrid::New();
  this->ThresholdGrid->Allocate(this->NumberOfCells);


  this->ThresholdGrid->SetFieldData(this->Grid->GetFieldData());

  vtkPointData *oldPd = this->Grid->GetPointData();
  vtkPointData* pd = this->ThresholdGrid->GetPointData();
  pd->CopyGlobalIdsOn();
  pd->CopyAllocate(oldPd);

  vtkCellData *oldCd = this->Grid->GetCellData();
  vtkCellData *cd = this->ThresholdGrid->GetCellData();
  cd->CopyGlobalIdsOn();
  cd->CopyAllocate(oldCd);

  vtkPoints* newPoints = vtkPoints::New();
  if(this->DoubleBased)
    {
    newPoints->SetDataTypeToDouble();
    }
  else
    {
    newPoints->SetDataTypeToFloat();
    }
  newPoints->Allocate(this->NumberOfPoints);

  vtkIdList *pointMap = vtkIdList::New();
  pointMap->SetNumberOfIds(this->NumberOfPoints);
  for(vtkIdType i=0; i < this->NumberOfPoints; ++i)
    {
    pointMap->SetId(i,-1);
    }

  double pt[3];
  vtkIdType numCellPts=0, ptId=0, newId=0, newCellId=0;
  vtkIdList *newCellPts = vtkIdList::New();
  vtkIdList *cellPts = NULL;
  for(vtkIdType cellId=0; cellId < this->NumberOfCells; ++cellId)
    {
    vtkCell *cell = this->Grid->GetCell(cellId);
    cellPts = cell->GetPointIds();
    numCellPts = cell->GetNumberOfPoints();

    if(this->CellProperties->IsCellDead(cellId) && numCellPts > 0)
        {
        for (vtkIdType i=0; i < numCellPts; i++)
          {
          ptId = cellPts->GetId(i);
          if ( (newId = pointMap->GetId(ptId)) < 0 )
            {
            this->Grid->GetPoint(ptId, pt);
            newId = newPoints->InsertNextPoint(pt);
            pointMap->SetId(ptId,newId);
            pd->CopyData(oldPd,ptId,newId);
            }
          newCellPts->InsertId(i,newId);
          }
        newCellId = this->ThresholdGrid->InsertNextCell(
                                          cell->GetCellType(),newCellPts);
        cd->CopyData(oldCd,cellId,newCellId);
        newCellPts->Reset();
      }
    }

  pointMap->Delete();
  newCellPts->Delete();

  this->ThresholdGrid->SetPoints(newPoints);
  newPoints->FastDelete();

  this->ThresholdGrid->Squeeze();
  cd->RemoveArray("vtkGhostLevels");

  return this->ThresholdGrid;
}
