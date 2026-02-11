setData(const QModelIndex& index, const QVariant& value, int role)
{
  Q_D(KCheckableProxyModel);
  if (role == Qt::CheckStateRole)
  {
    if (index.column() != 0)
      return false;
    if (!d->m_itemSelectionModel)
      return false;

    Qt::CheckState state = static_cast<Qt::CheckState>(value.toInt());
    const QModelIndex srcIndex = mapToSource(index);
    bool result = select(QItemSelection(srcIndex, srcIndex), state == Qt::Checked ? QItemSelectionModel::Select : QItemSelectionModel::Deselect);
    emit dataChanged(index, index);
    return result;
  }
  return KIdentityProxyModel::setData(index, value, role);
}
