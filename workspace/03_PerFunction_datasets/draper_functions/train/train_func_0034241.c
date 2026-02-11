FreeSearchStructure()
{
  if (this->Top)
    {
    vtkKdTree::DeleteAllDescendants(this->Top);
    this->Top->Delete();
    this->Top = NULL;
    }
  if (this->RegionList)
    {
    delete [] this->RegionList;
    this->RegionList = NULL;
    }

  this->NumberOfRegions = 0;
  this->SetActualLevel();

  this->DeleteCellLists();

  if (this->CellRegionList)
    {
    delete [] this->CellRegionList;
    this->CellRegionList = NULL;
    }

  if (this->LocatorPoints)
    {
    delete [] this->LocatorPoints;
    this->LocatorPoints = NULL;
    }

  if (this->LocatorIds)
    {
    delete [] this->LocatorIds;
    this->LocatorIds = NULL;
    }

  if (this->LocatorRegionLocation)
    {
    delete [] this->LocatorRegionLocation;
    this->LocatorRegionLocation = NULL;
    }
}
