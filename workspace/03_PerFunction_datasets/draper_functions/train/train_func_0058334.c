data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_errors.count())
        return QVariant();

    switch(role)
    {
    case Qt::DisplayRole:
        return QVariant(m_errors.at(index.row()).second);
    case Qt::ToolTipRole:
        return QVariant(m_errors.at(index.row()).first);
    default:
        return QVariant();
    }
}
