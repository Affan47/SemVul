addLineSegments(const CoordinateSequence& pts)
{
  size_t npts = pts.size();
  double lineLen = 0.0;
  for (size_t i = 0; i < npts - 1; i++) {
    double segmentLen = pts[i].distance(pts[i + 1]);
    if (segmentLen == 0.0)
      continue;

    lineLen += segmentLen;

    double midx = (pts[i].x + pts[i + 1].x) / 2;
    lineCentSum.x += segmentLen * midx;
    double midy = (pts[i].y + pts[i + 1].y) / 2;
    lineCentSum.y += segmentLen * midy;
  }
  totalLength += lineLen;
  if (lineLen == 0.0 && npts > 0)
    addPoint(pts[0]);
}
