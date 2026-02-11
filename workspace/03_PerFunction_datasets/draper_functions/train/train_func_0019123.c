parent(const QModelIndex & index) const
{
     if( !index.isValid() )
         return QModelIndex();

     CollectionTreeItem *childItem = static_cast<CollectionTreeItem*>(index.internalPointer());
     CollectionTreeItem *parentItem = childItem->parent();

     if ( (parentItem == m_rootItem) || !parentItem )
         return QModelIndex();

     return createIndex(parentItem->row(), 0, parentItem);
}
