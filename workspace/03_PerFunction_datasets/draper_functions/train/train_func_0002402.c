selectSegment(Segment* segment)
{
  ASSERT_ENGAUGE(segment != 0);
  Q3CanvasItemList list = segment->lines();

  selectItemsReplace(&list);
}
