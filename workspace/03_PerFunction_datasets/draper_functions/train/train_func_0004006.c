RasterizeGridTriangle(const int p1[2], const int p2[2], const int p3[2], RNScalar value)
{
  R2Point points[3];
  points[0][0] = p1[0];
  points[0][1] = p1[1];
  points[1][0] = p2[0];
  points[1][1] = p2[1];
  points[2][0] = p3[0];
  points[2][1] = p3[1];
  RasterizeGridPolygon(R2Polygon(points,3), value);
}
