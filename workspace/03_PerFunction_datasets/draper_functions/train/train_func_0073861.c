parent( const QModelIndex & index ) const
{
    if (!index.isValid())
        return QModelIndex();
    KDirModelNode* childNode = static_cast<KDirModelNode*>(index.internalPointer());
    Q_ASSERT(childNode);
    KDirModelNode* parentNode = childNode->parent();
    Q_ASSERT(parentNode);
    return d->indexForNode(parentNode);
}
