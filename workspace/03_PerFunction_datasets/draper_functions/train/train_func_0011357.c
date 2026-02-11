DeleteCellLists()
{
  int i;
  int num = this->CellList.nRegions;

  if (this->CellList.regionIds)
    {
    delete [] this->CellList.regionIds;
    }

  if (this->CellList.cells)
    {
    for (i=0; i<num; i++)
      {
      this->CellList.cells[i]->Delete();
      }

    delete [] this->CellList.cells;
    }

  if (this->CellList.boundaryCells)
    {
    for (i=0; i<num; i++)
      {
      this->CellList.boundaryCells[i]->Delete();
      }
    delete [] this->CellList.boundaryCells;
    }

  if (this->CellList.emptyList)
    {
    this->CellList.emptyList->Delete();
    }

  this->InitializeCellLists();

  return;
}
