flags(const QModelIndex &index) const
{
  if (!index.isValid() || !sourceModel())
    return QAbstractProxyModel::flags(index);

  const QModelIndex srcIndex = mapToSource(index);
  Q_ASSERT(srcIndex.isValid());
  return sourceModel()->flags(srcIndex);
}
