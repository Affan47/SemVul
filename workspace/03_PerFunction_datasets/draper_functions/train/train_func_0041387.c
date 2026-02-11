flags( const QModelIndex &idx ) const
{
    if( !idx.isValid() )
        return 0;

    Qt::ItemFlags flags = CollectionTreeItemModelBase::flags( idx );
    if( idx.parent().isValid() )
        return flags;


    CollectionTreeItem *item = static_cast<CollectionTreeItem*>( idx.internalPointer() );
    Q_ASSERT(item->type() == CollectionTreeItem::Collection);
    if( m_dragSourceCollections.contains( item->parentCollection() ) )
        return flags;

    if( !item->parentCollection()->isWritable() )
        return flags;


    return flags | Qt::ItemIsDropEnabled;
}
