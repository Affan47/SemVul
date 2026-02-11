FullRangeNeeded(const Polygon &pts)
{
  bool result = false;
  for (Polygon::size_type i = 0; i <  pts.size(); ++i)
  {
    if (Abs(pts[i].X) > hiRange || Abs(pts[i].Y) > hiRange)
        throw "Coordinate exceeds range bounds.";
      else if (Abs(pts[i].X) > loRange || Abs(pts[i].Y) > loRange)
        result = true;
  }
  return result;
}
