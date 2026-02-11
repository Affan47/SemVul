appendDocumentToList(QString doc)
{
  if ((int) m_mruDocuments.count() < m_mruMax)
  {
    QAction* pAction = new QAction(doc, 0);
    CHECK_PTR_ENGAUGE(pAction);
    m_mruDocuments.append(pAction);
  }
}
