AddIntermediatePointWorldPosition( int n, double pos[3], vtkIdType ptId )
{
  if ( n < 0 ||
       static_cast<unsigned int>(n) >= this->Internal->Nodes.size() )
    {
    return 0;
    }

  vtkContourRepresentationPoint *point = new vtkContourRepresentationPoint;
  point->WorldPosition[0] = pos[0];
  point->WorldPosition[1] = pos[1];
  point->WorldPosition[2] = pos[2];
  point->PointId = ptId;

  double worldOrient[9] = {1.0,0.0,0.0,
                           0.0,1.0,0.0,
                           0.0,0.0,1.0};

  this->GetRendererComputedDisplayPositionFromWorldPosition(
                          pos, worldOrient, point->NormalizedDisplayPosition );
  this->Renderer->DisplayToNormalizedDisplay(
      point->NormalizedDisplayPosition[0],
      point->NormalizedDisplayPosition[1] );

  this->Internal->Nodes[n]->Points.push_back(point);
  return 1;
}
