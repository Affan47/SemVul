GetCellNeighbors(vtkIdType cellId, vtkIdList *ptIds,
                                           vtkIdList *cellIds)
{
  int i, j, k;
  int numPts, minNumCells, numCells;
  vtkIdType *pts, ptId, *cellPts, *cells;
  vtkIdType *minCells = NULL;
  int match;
  vtkIdType minPtId = 0, npts;

  if ( ! this->Links )
    {
    this->BuildLinks();
    }

  cellIds->Reset();


  numPts = ptIds->GetNumberOfIds();
  pts = ptIds->GetPointer(0);
  for (minNumCells=VTK_LARGE_INTEGER,i=0; i<numPts; i++)
    {
    ptId = pts[i];
    numCells = this->Links->GetNcells(ptId);
    cells = this->Links->GetCells(ptId);
    if ( numCells < minNumCells )
      {
      minNumCells = numCells;
      minCells = cells;
      minPtId = ptId;
      }
    }

  if (minNumCells == VTK_LARGE_INTEGER && numPts == 0) {
    vtkErrorMacro("input point ids empty.");
    minNumCells = 0;
  }


  for (i=0; i<minNumCells; i++)
    {
    if ( minCells[i] != cellId )
      {
      this->GetCellPoints(minCells[i],npts,cellPts);
      for (match=1, j=0; j<numPts && match; j++)
        {
        if ( pts[j] != minPtId )
          {
          for (match=k=0; k<npts; k++)
            {
            if ( pts[j] == cellPts[k] )
              {
              match = 1;
              break;
              }
            }
          }
        }
      if ( match )
        {
        cellIds->InsertNextId(minCells[i]);
        }
      }
    }
}
