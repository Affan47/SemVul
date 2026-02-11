index(int row, int column, const QModelIndex &parent) const
{
    Q_D(const KSelectionProxyModel);

    if (!sourceModel() || d->m_rootIndexList.isEmpty() || !hasIndex(row, column, parent))
        return QModelIndex();

    Q_ASSERT(parent.isValid() ? parent.model() == this : true);

    if (!parent.isValid())
        return d->createTopLevelIndex(row, column);

    void * const parentId = d->parentId(parent);
    Q_ASSERT(parentId);
    return createIndex(row, column, parentId);
}
