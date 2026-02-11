findIndex(const QList<int> &rows) const
{
  const int col = 0;
  QModelIndex parent = QModelIndex();
  QListIterator<int> i(rows);
  while (i.hasNext())
  {
    parent = m_model->index(i.next(), col, parent);
    Q_ASSERT(parent.isValid());
  }
  return parent;
}
