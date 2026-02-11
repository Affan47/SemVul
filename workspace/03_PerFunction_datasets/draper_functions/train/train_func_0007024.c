FindClosestPoint(double x, double y, double z, double &dist2)
{
  if (!this->LocatorPoints)
    {
    vtkErrorMacro(<< "vtkKdTree::FindClosestPoint: must build locator first");
    return -1;
    }

  double minDistance2 = 0.0;

  int closeId=-1, newCloseId=-1;
  double newDistance2 = 4 * this->MaxWidth * this->MaxWidth;

  int regionId = this->GetRegionContainingPoint(x, y, z);

  if (regionId < 0)
    {


    double pt[3];
    this->Top->GetDistance2ToBoundary(x, y, z, pt, 1);

    double *min = this->Top->GetMinBounds();
    double *max = this->Top->GetMaxBounds();


    if (pt[0] <= min[0])
      {
      pt[0] = min[0] + this->FudgeFactor;
      }
    if (pt[1] <= min[1])
      {
      pt[1] = min[1] + this->FudgeFactor;
      }
    if (pt[2] <= min[2])
      {
      pt[2] = min[2] + this->FudgeFactor;
      }
    if (pt[0] >= max[0])
      {
      pt[0] = max[0] - this->FudgeFactor;
      }
    if (pt[1] >= max[1])
      {
      pt[1] = max[1] - this->FudgeFactor;
      }
    if (pt[2] >= max[2])
      {
      pt[2] = max[2] - this->FudgeFactor;
      }

    regionId = this->GetRegionContainingPoint(pt[0], pt[1], pt[2]);

    closeId = this->_FindClosestPointInRegion(regionId,
                                              x, y, z,
                                              minDistance2);


    newCloseId =
      this->FindClosestPointInSphere(x, y, z,
                                     sqrt(minDistance2),
                                     regionId,
                                     newDistance2);

    }
  else
    {
    closeId =
      this->_FindClosestPointInRegion(regionId, x, y, z, minDistance2);

    if (minDistance2 > 0.0)
      {
      float dist2ToBoundary =
        this->RegionList[regionId]->GetDistance2ToInnerBoundary(x, y, z);

      if (dist2ToBoundary < minDistance2)
        {


        newCloseId = this->FindClosestPointInSphere(x, y, z,
                                                    sqrt(minDistance2),
                                                    regionId,
                                                    newDistance2);
        }
      }
    }

  if (newDistance2 < minDistance2 && newCloseId != -1)
    {
    closeId = newCloseId;
    minDistance2 = newDistance2;
    }

  vtkIdType closePointId = static_cast<vtkIdType>(this->LocatorIds[closeId]);

  dist2 = minDistance2;

  return closePointId;
}
