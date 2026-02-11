prependDocumentToList(QString doc)
{

  QAction* pAction = new QAction(doc, 0);
  CHECK_PTR_ENGAUGE(pAction);
  m_mruDocuments.prepend(pAction);


  if ((int) m_mruDocuments.count() > m_mruMax)
  {
    pAction = m_mruDocuments.last();
    m_mruDocuments.removeLast();

    ASSERT_ENGAUGE(pAction != 0);
    delete pAction;
  }
}
