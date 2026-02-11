GetCellPoints(vtkIdType cellId, vtkIdList *ptIds)
{
  vtkIdType i, loc;
  vtkIdType *pts, numPts;

  loc = this->Locations->GetValue(cellId);
  this->Connectivity->GetCell(loc,numPts,pts);
  ptIds->SetNumberOfIds(numPts);
  for (i=0; i<numPts; i++)
    {
    ptIds->SetId(i,pts[i]);
    }

}
