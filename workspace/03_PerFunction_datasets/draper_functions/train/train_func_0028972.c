TemplateTriangulate(int cellType,
                                                 int numPts, int numEdges)
{
  this->CellType = cellType;
  if ( ! this->UseTemplates )
    {
    this->Triangulate();
    return;
    }

  this->NumberOfCellPoints = numPts;
  this->NumberOfCellEdges = numEdges;


  if ( ! this->PreSorted )
    {
    if (this->UseTwoSortIds)
      {
      qsort(this->Mesh->Points.GetPointer(0), this->NumberOfPoints,
            sizeof(OTPoint), vtkSortOnTwoIds);
      }
    else
      {
      qsort(this->Mesh->Points.GetPointer(0), this->NumberOfPoints,
            sizeof(OTPoint), vtkSortOnIds);
      }
    }

  if ( ! this->TemplateTriangulation() )
    {
    int preSorted = this->PreSorted;
    this->PreSorted = 1;
    this->Triangulate();
    this->AddTemplate();
    this->PreSorted = preSorted;
    }
}
