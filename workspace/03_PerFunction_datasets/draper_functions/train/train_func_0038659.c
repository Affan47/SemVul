setCollectionStatus( const QString &collectionId, CollectionStatus status )
{
    foreach( const CollectionPair &pair, d->collections )
    {
        if( pair.first->collectionId() == collectionId )
        {
            if( ( pair.second & CollectionViewable ) &&
               !( status & CollectionViewable ) )
            {
                emit collectionRemoved( collectionId );
            }
            else if( ( pair.second & CollectionQueryable ) &&
                    !( status & CollectionViewable ) )
            {
                emit collectionAdded( pair.first );
                emit collectionAdded( pair.first, pair.second );
            }
            CollectionPair &pair2 = const_cast<CollectionPair&>( pair );
            pair2.second = status;
            const QMetaObject *mo = metaObject();
            const QMetaEnum me = mo->enumerator( mo->indexOfEnumerator( "CollectionStatus" ) );
            KGlobal::config()->group( "CollectionManager" ).writeEntry( collectionId, me.valueToKey( status ) );
            break;
        }
    }
}
