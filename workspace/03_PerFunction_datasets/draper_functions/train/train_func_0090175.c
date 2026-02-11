RealCoord(icoord)
real icoord;
{
  real coord, cfloor, cfract;
  int lon, neg;
  coord = icoord;
  lon = 0; neg = 0;
  if (coord > 180.0) {
    coord = coord - 360.0;
    lon = 1;
  }
  if (coord < 0.0) {
    coord = -coord;
    neg = 1;
  }
  cfloor = RFloor(coord);
  cfract = RFract(coord);
  cfract = cfract / 0.6;
  coord = cfloor + cfract;
  if (neg)
    coord = -coord;
  if (lon)
    coord = 360.0 - coord;
  return coord;
}
