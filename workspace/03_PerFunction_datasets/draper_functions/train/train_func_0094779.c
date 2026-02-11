organizeTracks( const QSet<CollectionTreeItem *> &items ) const
{
    DEBUG_BLOCK
    if( !items.count() )
        return;


    Collections::QueryMaker *qm = createMetaQueryFromItems( items, true );
    if( !qm )
        return;

    CollectionTreeItem *item = items.toList().first();
    while( item->isDataItem() )
        item = item->parent();

    Collection *coll = item->parentCollection();
    CollectionLocation *location = coll->location();
    if( !location->isOrganizable() )
    {
        debug() << "Collection not organizable";

        delete location;
        delete qm;
        return;
    }
    location->prepareMove( qm, coll->location() );
}
