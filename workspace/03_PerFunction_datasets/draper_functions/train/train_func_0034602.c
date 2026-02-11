_FindClosestPointInRegion(
  int leafNodeId, double x, double y, double z, double &dist2)
{
  int minId=0;

  float fx = static_cast<float>(x);
  float fy = static_cast<float>(y);
  float fz = static_cast<float>(z);

  float minDistance2 = 4 * this->MaxWidth * this->MaxWidth;

  int idx = this->LeafNodeList[leafNodeId]->GetMinID();

  float *candidate = this->LocatorPoints + (idx * 3);

  int numPoints = this->LeafNodeList[leafNodeId]->GetNumberOfPoints();
  for (int i=0; i < numPoints; i++)
    {
    float diffx = fx-candidate[0];
    float diffy = fy-candidate[1];
    float diffz = fz-candidate[2];
    float dxyz = diffx*diffx + diffy*diffy + diffz*diffz;
    if(dxyz < minDistance2)
      {
      minId = idx + i;
      minDistance2 = dxyz;
      if(dxyz == 0.0)
        {
        break;
        }
      }

    candidate += 3;
    }

  dist2 = minDistance2;

  return minId;
}
