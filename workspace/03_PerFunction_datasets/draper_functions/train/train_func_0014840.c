createCollectionActions( const QModelIndexList &indices )
{
    QActionList actions;


    CollectionTreeItem *item =
            static_cast<CollectionTreeItem *>( indices.first().internalPointer() );


    if( item->isDataItem() )
        return actions;

    Collection *collection = item->parentCollection();


    QScopedPointer<Capabilities::ActionsCapability> cc(
                collection->create<Capabilities::ActionsCapability>() );

    if( cc )
        actions = cc->actions();

    return actions;
}
