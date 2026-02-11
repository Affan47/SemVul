AddNewCellsDataSet(vtkDataSet *set, vtkIdType *idMap)
{
  vtkIdType oldCellId, id, newPtId, newCellId = 0, oldPtId;

  vtkUnstructuredGrid *ugrid = this->UnstructuredGrid;
  vtkCellData *cellArrays = set->GetCellData();
  vtkIdType numCells      = set->GetNumberOfCells();

  vtkIdList *cellPoints = vtkIdList::New();
  cellPoints->Allocate(VTK_CELL_SIZE);

  vtkIdType nextCellId = 0;

  int duplicateCellTest = 0;

  if (this->UseGlobalCellIds)
    {
    int success = this->GlobalCellIdAccessStart(set);

    if (success)
      {
      nextCellId = this->GlobalCellIdMap->IdTypeMap.size();
      duplicateCellTest = 1;
      }
    }

  for (oldCellId=0; oldCellId < numCells; oldCellId++)
    {
    if (duplicateCellTest)
      {
      vtkIdType globalId = this->GlobalCellIdAccessGetId(oldCellId);

      std::pair<std::map<vtkIdType, vtkIdType>::iterator, bool> inserted =

        this->GlobalCellIdMap->IdTypeMap.insert(
           std::map<vtkIdType, vtkIdType>::value_type(globalId, nextCellId));

      if (inserted.second)
        {
        nextCellId++;
        }
      else
        {
        continue;
        }
      }

    set->GetCellPoints(oldCellId, cellPoints);

    for (id=0; id < cellPoints->GetNumberOfIds(); id++)
      {
      oldPtId = cellPoints->GetId(id);

      if (idMap)
        {
        newPtId = idMap[oldPtId];
        }
      else
        {
        newPtId = this->NumberOfPoints + oldPtId;
        }
      cellPoints->SetId(id, newPtId);
      }

    newCellId =
      (vtkIdType)ugrid->InsertNextCell(set->GetCellType(oldCellId), cellPoints);

    ugrid->GetCellData()->CopyData(*(this->cellList), cellArrays,
                                   this->nextGrid, oldCellId, newCellId);
    }

  cellPoints->Delete();

  return newCellId;
}
