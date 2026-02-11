removePoints()
{
  QList<QRect> updateRectList;

  Point* p;
  Point* pNext;
  for (p = m_points.first(); p; p = pNext)
  {
    pNext = m_points.next();
    removePoint(p, &updateRectList);
  }

  m_modifiedGeometry = true;
}
