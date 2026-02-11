reMapPointIds(vtkDataSet *grid)
{
  int totalPoints = grid->GetNumberOfPoints();

  char *temp = new char [totalPoints];

  if (!temp)
    {
    vtkErrorMacro(<< "vtkExtractCells::reMapPointIds memory allocation");
    return NULL;
    }
  memset(temp, 0, totalPoints);

  int numberOfIds = 0;
  int i;
  vtkIdType id;
  vtkIdList *ptIds = vtkIdList::New();
  std::set<vtkIdType>::iterator cellPtr;

  if (!this->InputIsUgrid)
    {
    for (cellPtr = this->CellList->IdTypeSet.begin();
         cellPtr != this->CellList->IdTypeSet.end();
         ++cellPtr)
      {
      grid->GetCellPoints(*cellPtr, ptIds);

      vtkIdType nIds = ptIds->GetNumberOfIds();

      vtkIdType *ptId = ptIds->GetPointer(0);

      for (i=0; i<nIds; i++)
        {
        id = *ptId++;

        if (temp[id] == 0)
          {
          numberOfIds++;
          temp[id] = 1;
          }
        }
      }
    }
  else
    {
    vtkUnstructuredGrid *ugrid = vtkUnstructuredGrid::SafeDownCast(grid);

    this->SubSetUGridCellArraySize = 0;

    vtkIdType *cellArray = ugrid->GetCells()->GetPointer();
    vtkIdType *locs = ugrid->GetCellLocationsArray()->GetPointer(0);

    this->SubSetUGridCellArraySize = 0;
    vtkIdType maxid = ugrid->GetCellLocationsArray()->GetMaxId();

    for (cellPtr = this->CellList->IdTypeSet.begin();
         cellPtr != this->CellList->IdTypeSet.end();
         ++cellPtr)
      {
      if (*cellPtr > maxid) continue;

      int loc = locs[*cellPtr];

      vtkIdType nIds = cellArray[loc++];

      this->SubSetUGridCellArraySize += (1 + nIds);

      for (i=0; i<nIds; i++)
        {
        id = cellArray[loc++];

        if (temp[id] == 0)
          {
          numberOfIds++;
          temp[id] = 1;
          }
        }
      }
    }

  ptIds->SetNumberOfIds(numberOfIds);
  int next=0;

  for (id=0; id<totalPoints; id++)
    {
    if (temp[id]) ptIds->SetId(next++, id);
    }

  delete [] temp;

  return ptIds;
}
