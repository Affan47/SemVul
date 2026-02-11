updateModel()
{
    d->mapping.clear();
    d->proxySourceParent.clear();
    for (int i = 0; i<d->m_Model->rowCount(); ++i) {
        QModelIndex idx = d->m_Model->index(i, 0);
        updateBranch(idx);
    }
    Q_EMIT layoutChanged();
}
