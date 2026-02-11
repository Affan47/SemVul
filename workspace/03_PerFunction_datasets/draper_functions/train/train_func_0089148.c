IntersectsSphere2(int regionId, double x, double y, double z,
                                double rSquared)
{
  REGIONIDCHECK_RETURNERR(regionId, 0);

  vtkKdNode *node = this->RegionList[regionId];

  return node->IntersectsSphere2(x, y, z, rSquared,
                     this->ComputeIntersectionsUsingDataBounds);
}
