FindPointsInArea(vtkKdNode* node, double* area, vtkIdTypeArray* ids)
{
  double b[6];
  node->GetBounds(b);

  if (b[0] > area[1] || b[1] < area[0] ||
    b[2] > area[3] || b[3] < area[2] ||
    b[4] > area[5] || b[5] < area[4])
    {
    return;
    }

  bool contains = false;
  if (area[0] <= b[0] && b[1] <= area[1] &&
    area[2] <= b[2] && b[3] <= area[3] &&
    area[4] <= b[4] && b[5] <= area[5])
    {
    contains = true;
    }

  if (contains)
    {
    this->AddAllPointsInRegion(node, ids);
    }
  else
    {
    if (node->GetLeft() == NULL)
      {
      int regionID = node->GetID();
      int regionLoc = this->LocatorRegionLocation[regionID];
      float* pt = this->LocatorPoints + (regionLoc * 3);
      vtkIdType numPoints = this->RegionList[regionID]->GetNumberOfPoints();
      for (vtkIdType i = 0; i < numPoints; i++)
        {
        if (area[0] <= pt[0] && pt[0] <= area[1] &&
          area[2] <= pt[1] && pt[1] <= area[3] &&
          area[4] <= pt[2] && pt[2] <= area[5])
          {
          vtkIdType ptId = static_cast<vtkIdType>(this->LocatorIds[regionLoc + i]);
          ids->InsertNextValue(ptId);
          }
        pt += 3;
        }
      }
    else
      {
      this->FindPointsInArea(node->GetLeft(), area, ids);
      this->FindPointsInArea(node->GetRight(), area, ids);
      }
    }
}
