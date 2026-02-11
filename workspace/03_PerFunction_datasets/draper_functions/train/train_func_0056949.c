listBounds(Q3CanvasItemList* list)
{
  int xMin = 0, yMin = 0, xMax = 1, yMax = 1;
  bool first = true;
  Q3CanvasItemList::iterator itr;
  ASSERT_ENGAUGE(list != 0);
  for (itr = list->begin(); itr != list->end(); ++itr)
  {
    ASSERT_ENGAUGE((*itr) != 0);
    QRect bounds = (*itr)->boundingRect();

    if (first || (bounds.left() < xMin))
      xMin = bounds.left();
    if (first || (bounds.top() < yMin))
      yMin = bounds.top();
    if (first || (bounds.right() > xMax))
      xMax = bounds.right();
    if (first || (bounds.bottom() > yMax))
      yMax = bounds.bottom();

    first = false;
  }

  return QRect(QPoint(xMin, yMin), QPoint(xMax, yMax)).normalize();
}
