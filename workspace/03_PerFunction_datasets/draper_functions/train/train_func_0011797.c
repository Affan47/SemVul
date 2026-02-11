LookForNeighbors(vtkPolyData* model, vtkIdType pointId, vtkIdList* notVisitedIds, vtkIdTypeArray* edgeTableForIncludedGlobalProfiles)
{
  vtkIdTypeArray* marksArray = vtkIdTypeArray::SafeDownCast(model->GetPointData()->GetArray(MarksArrayName));

  bool someNeighborsFound = false;

  unsigned short ncells; vtkIdType *cell;
  model->GetPointCells(pointId,ncells,cell);
  vtkIdType i;
  for (i=0; i<ncells; i++)
    {
    vtkIdType npts; vtkIdType* pts;
    model->GetCellPoints(cell[i],npts,pts);
    vtkIdType j;
    for (j=0; j<npts; j++)
      {
      if (pts[j]!=pointId)
        {
        vtkIdType scalar = marksArray->GetValue(pts[j]);
        if (scalar == NON_VISITED)
          {
          notVisitedIds->InsertUniqueId(pts[j]);
          someNeighborsFound=true;
          }
        else if (scalar == GLOBAL)
          {
          this->InsertInEdgeTable(edgeTableForIncludedGlobalProfiles,pointId,pts[j]);
          }
        }
      }
    }

  return someNeighborsFound;
}
