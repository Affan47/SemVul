updateBranch(QModelIndex &rootIndex)
{
    if (d->m_Model->isCategory(rootIndex)) {
        QModelIndex proxy = createIndex(rootIndex.row(), rootIndex.column(), rootIndex.internalPointer());
        d->mapping.insert(QPersistentModelIndex(rootIndex), proxy);
        QModelIndex sourceParent;
        if (rootIndex.parent().isValid())
            sourceParent = rootIndex.parent();
        d->proxySourceParent.insert(proxy, sourceParent);


        for(int i = 0; i < d->m_Model->rowCount(rootIndex); ++i) {
            QModelIndex idx = d->m_Model->index(i, 0, rootIndex);
            updateBranch(idx);
        }
    }
}
