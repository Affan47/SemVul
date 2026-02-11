slotMoveTracks( const Meta::TrackList& tracks )
{
    if( !m_moveDestinationCollection )
        return;

    QSet<Collections::Collection *> collections;
    foreach( const Meta::TrackPtr &track, tracks )
    {
        collections.insert( track->collection() );
    }

    if( collections.count() == 1 )
    {
        Collections::Collection *sourceCollection = collections.values().first();
        Collections::CollectionLocation *source;
        if( sourceCollection )
            source = sourceCollection->location();
        else
            source = new Collections::FileCollectionLocation();

        Collections::CollectionLocation *destination = m_moveDestinationCollection.data()->location();
        source->prepareMove( tracks, destination );
    }
    else
        warning() << "Cannot handle moving tracks from multiple collections, doing nothing to be safe";

    m_moveDestinationCollection.clear();
}
