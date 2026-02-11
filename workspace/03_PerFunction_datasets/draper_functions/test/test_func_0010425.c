LookForIntersectingPoint(vtkPoints* segmentPoints, double center[3], double radius, vtkIdType &intersectingPointId)
{
  intersectingPointId = segmentPoints->GetNumberOfPoints()-1;
  vtkIdType i;
  for (i=segmentPoints->GetNumberOfPoints()-2; i>=0; i--)
    {
    double segmentPoint[3];
    segmentPoints->GetPoint(i,segmentPoint);
    if (this->Distance(center,segmentPoint)>radius)
      {
      intersectingPointId = i+1;
      break;
      }
    }
}
