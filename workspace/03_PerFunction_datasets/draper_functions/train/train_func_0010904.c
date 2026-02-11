clear(QList<QRect>* updateRectList)
{
  if (m_highlightCandidate)
  {
    updateRectList->append(m_highlightCandidate->boundingRect());
    delete m_highlightCandidate;
    m_highlightCandidate = 0;
  }

  while (m_matchList.count() > 0)
  {
    ASSERT_ENGAUGE(updateRectList != 0);
    updateRectList->append(m_matchList.last()->boundingRect());

    m_matchList.removeLast();
  }
}
