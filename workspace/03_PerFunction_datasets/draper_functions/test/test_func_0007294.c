GetRegionContainingCell(vtkDataSet *set, vtkIdType cellID)
{
  int regionID = -1;

  if ( this->GetDataSetIndex(set) < 0)
    {
    vtkErrorMacro(<<"vtkKdTree::GetRegionContainingCell no such data set");
    return -1;
    }
  if ( (cellID < 0) || (cellID >= set->GetNumberOfCells()))
    {
    vtkErrorMacro(<<"vtkKdTree::GetRegionContainingCell bad cell ID");
    return -1;
    }

  if (this->CellRegionList)
    {
    if (set == this->GetDataSet())
      {
      return this->CellRegionList[cellID];
      }

    int setNum = this->GetDataSetIndex(set);

    int offset = this->GetDataSetsNumberOfCells(0, setNum-1);

    return this->CellRegionList[offset + cellID];
    }

  float center[3];

  this->ComputeCellCenter(set, cellID, center);

  regionID = this->GetRegionContainingPoint(center[0], center[1], center[2]);

  return regionID;
}
