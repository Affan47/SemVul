showSegment(bool toggle, SegmentSettings seg, QList<QRect>* updateRectList)
{
  SegmentLine* line;
  for (line = m_lines.first(); line; line = m_lines.next())
  {
    ASSERT_ENGAUGE(line != 0);
    line->setVisible(toggle);

    if (toggle)
    {
      QRect updateRect = QRect(
        line->startPoint(),
        line->endPoint()).normalize();
      updateRect.setLeft(updateRect.left() - seg.lineSize);
      updateRect.setTop(updateRect.top() - seg.lineSize);
      updateRect.setRight(updateRect.right() + seg.lineSize);
      updateRect.setBottom(updateRect.bottom() + seg.lineSize);

      updateRectList->append(updateRect);
    }
  }
}
