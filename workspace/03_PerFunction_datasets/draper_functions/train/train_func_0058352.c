setData(const QModelIndex &item, const QVariant &value, int role)
{
    QModelIndex idx = m_Model->index(item.row(), item.column());
    if (m_Model->setData(idx, value, role)) {
        Q_EMIT dataChanged(idx, idx);
        return true;
    }
    return false;
}
