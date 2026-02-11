headerData(int section, Qt::Orientation orientation, int role) const
{
  if (!sourceModel() || columnCount() <= section)
    return QVariant();

  return QAbstractProxyModel::headerData(section, orientation, role);
}
