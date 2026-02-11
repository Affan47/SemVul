addFillet(const Coordinate &p, const Coordinate &p0,
  const Coordinate &p1, int direction, double radius)
{
  double dx0 = p0.x - p.x;
  double dy0 = p0.y - p.y;
  double startAngle = atan2(dy0, dx0);
  double dx1 = p1.x - p.x;
  double dy1 = p1.y - p.y;
  double endAngle = atan2(dy1, dx1);

  if (direction == CGAlgorithms::CLOCKWISE) {
    if (startAngle <= endAngle) startAngle += 2.0 * PI;
  }
  else {
    if (startAngle >= endAngle) startAngle -= 2.0 * PI;
  }

  segList.addPt(p0);
  addFillet(p, startAngle, endAngle, direction, radius);
  segList.addPt(p1);
}
