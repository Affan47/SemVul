setCurrentAnchorPoint(Point3 point)
{
  for (int i = 0; i < 3; i++) {
    pickInfo->anchorPoint[i] = point[i];
  }
}
