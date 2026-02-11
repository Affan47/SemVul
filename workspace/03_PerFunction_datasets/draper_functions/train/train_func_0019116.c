removeUnneededLines(int* foldedLines)
{


  SegmentLine* lineOlder = 0;
  SegmentLine* line;
  QList<QPoint> removedPoints;
  for (line = m_lines.first(); line; line = m_lines.next())
  {
    if (lineOlder != 0)
    {
      double xLeft = lineOlder->startPoint().x();
      double yLeft = lineOlder->startPoint().y();
      double xInt = lineOlder->endPoint().x();
      double yInt = lineOlder->endPoint().y();
      ASSERT_ENGAUGE(line != 0);
      double xRight = line->endPoint().x();
      double yRight = line->endPoint().y();

      if (pointIsCloseToLine(xLeft, yLeft, xInt, yInt, xRight, yRight) &&
        pointsAreCloseToLine(xLeft, yLeft, removedPoints, xRight, yRight))
      {

        ++(*foldedLines);
        removedPoints.append(QPoint((int) xInt, (int) yInt));
        m_lines.remove(lineOlder);
        line->setPoints((int) xLeft, (int) yLeft, (int) xRight, (int) yRight);
      }
      else

        removedPoints.clear();
    }

    lineOlder = line;
  }
}
