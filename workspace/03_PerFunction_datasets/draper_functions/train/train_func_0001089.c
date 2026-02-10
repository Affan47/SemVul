showSegments(bool toggle, SegmentSettings seg, QList<QRect>* updateRectList)
{
  int minPixels = (seg.minPoints - 1) * seg.pointSeparation;

  Segment* segment;
  for (segment = segments.first(); segment; segment = segments.next())
  {

    ASSERT_ENGAUGE(segment != 0);
    if (segment->length() < minPixels)
      segment->showSegment(false, seg, updateRectList);
    else
      segment->showSegment(toggle, seg, updateRectList);
  }
}
