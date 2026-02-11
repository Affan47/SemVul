purgeItem(qint64 parent)
{
  QList<QList<qint64> > childItemRows = m_model->m_childItems.value(parent);

  if (childItemRows.size() > 0)
  {
    for (int col = 0; col < m_numCols; col++)
    {
      QList<qint64> childItems = childItemRows[col];
      foreach(qint64 item, childItems)
      {
        purgeItem(item);
        m_model->m_childItems[parent][col].removeOne(item);
      }
    }
  }
  m_model->m_items.remove(parent);
}
