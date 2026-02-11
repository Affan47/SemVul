SegmentTopology(vtkCollection* bifurcations, vtkCollection* bifurcationsRadii, double firstSegmentPoint[3], double lastSegmentPoint[3], double firstPoint[3], double &firstRadius, double lastPoint[3], double &lastRadius, vtkIdType segmentTopology[2])
{
  segmentTopology[0] = segmentTopology[1] = 0;

  bool firstPointFound = false;
  bool lastPointFound = false;
  if (!lastSegmentPoint)
    {
    segmentTopology[1] = -1;
    lastPointFound = true;
    }

  vtkIdType i;
  bifurcations->InitTraversal();
  bifurcationsRadii->InitTraversal();
  for (i=0; i<bifurcations->GetNumberOfItems(); i++)
    {
    vtkPoints* bifurcation = (vtkPoints*)bifurcations->GetNextItemAsObject();
    vtkDoubleArray* bifurcationRadii = (vtkDoubleArray*)bifurcationsRadii->GetNextItemAsObject();
    vtkIdType j;
    for (j=0; j<bifurcation->GetNumberOfPoints(); j++)
      {
      if (i == 0 || (i > 0 && j > 0))
        {
        double point[3];
        bifurcation->GetPoint(j,point);
        if (!firstPointFound)
          {
          if (point[0] == firstSegmentPoint[0] && point[1] == firstSegmentPoint[1] && point[2] == firstSegmentPoint[2])
            {
            segmentTopology[0] = i;
            if (j > 0)
              {
              bifurcation->GetPoint(0,firstPoint);
              firstRadius = bifurcationRadii->GetValue(j);
              }
            firstPointFound = true;
            }
          }
        if (lastSegmentPoint && !lastPointFound)
          {
          if (point[0] == lastSegmentPoint[0] && point[1] == lastSegmentPoint[1] && point[2] == lastSegmentPoint[2])
            {
            segmentTopology[1] = i;
            if (j>0)
              {
              bifurcation->GetPoint(0,lastPoint);
              lastRadius = bifurcationRadii->GetValue(j);
              }
            lastPointFound = true;
            }
          }
        }
      if (firstPointFound && lastPointFound)
        {
        break;
        }
      }
    if (firstPointFound && lastPointFound)
      {
      break;
      }
    }
}
