GenerateNewProfiles(vtkPolyData* model, double center[3], double radius, vtkIdTypeArray* edgeTableForNewProfiles, vtkIdTypeArray* cellPairsForNewProfiles, vtkIdList* pointIdsForNewProfiles, vtkPolyDataCollection* newProfiles, vtkCollection* newProfilesEdgeTables)
{
  if (edgeTableForNewProfiles->GetNumberOfTuples())
    {
    vtkPoints* pointsForNewProfiles = vtkPoints::New();
    vtkDoubleArray* pointDistancesForNewProfiles = vtkDoubleArray::New();

    vtkIdType i;
    for (i=0; i<pointIdsForNewProfiles->GetNumberOfIds(); i++)
      {
      double point[3];
      model->GetPoint(pointIdsForNewProfiles->GetId(i),point);
      pointsForNewProfiles->InsertNextPoint(point);
      pointDistancesForNewProfiles->InsertNextValue(Distance(center,point));
      }

    vtkPoints* virtualPointsForNewProfiles = vtkPoints::New();
    vtkIdType edge[2];
    for (i=0; i<edgeTableForNewProfiles->GetNumberOfTuples(); i++)
      {
      this->GetFromEdgeTable(edgeTableForNewProfiles,i,edge);
      double virtualPoint[3];
      this->LocateVirtualPoint(edge,center,radius,pointIdsForNewProfiles,pointsForNewProfiles,pointDistancesForNewProfiles,virtualPoint);
      virtualPointsForNewProfiles->InsertNextPoint(virtualPoint);
      }

    this->ReconstructNewProfiles(virtualPointsForNewProfiles,edgeTableForNewProfiles,cellPairsForNewProfiles,newProfiles,newProfilesEdgeTables);

    pointsForNewProfiles->Delete();
    pointDistancesForNewProfiles->Delete();
    virtualPointsForNewProfiles->Delete();
    }
}
