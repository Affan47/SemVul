FindCell(double x[3], vtkCell* cell,
                                vtkGenericCell *gencell, vtkIdType cellId,
                                double tol2, int& subId, double pcoords[3],
                                double *weights)
{
  vtkIdType       ptId;
  double          closestPoint[3];
  double          dist2;
  vtkIdList       *cellIds;

  ptId = this->FindPoint(x);
  if ( ptId < 0 )
    {
    return (-1);
    }

  cellIds = vtkIdList::New();
  cellIds->Allocate(8,100);
  this->GetPointCells(ptId, cellIds);
  if ( cellIds->GetNumberOfIds() <= 0 )
    {
    cellIds->Delete();
    return -1;
    }

  int ii, num;
  num = cellIds->GetNumberOfIds();
  for (ii = 0; ii < num; ++ii)
    {
    cellId = cellIds->GetId(ii);
    if ( gencell )
      {
      this->GetCell(cellId, gencell);
      }
    else
      {
      cell = this->GetCell(cellId);
      }


    double dx[3];
    dx[0] = x[0];
    dx[1] = x[1];
    dx[2] = x[2];
    if ( ( gencell &&
           gencell->EvaluatePosition(dx,closestPoint,subId,
                                     pcoords, dist2,weights) == 1
           && dist2 <= tol2 )  ||
         ( !gencell &&
           cell->EvaluatePosition(dx,closestPoint,subId,
                                  pcoords, dist2,weights) == 1
           && dist2 <= tol2 ) )
      {
      cellIds->Delete();
      return cellId;
      }
    }


  vtkErrorMacro("Could not find cell.");
  return -1;
}
