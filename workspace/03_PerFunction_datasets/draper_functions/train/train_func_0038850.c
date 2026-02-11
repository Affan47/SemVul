getTrack( Meta::TrackPtr track )
{
    const Meta::TrackKey key( track );
    m_trackLock.lockForRead();
    if( m_trackMap.contains( key ) )
    {
        KSharedPtr<Meta::AggregateTrack> aggregateTrack = m_trackMap.value( key );
        aggregateTrack->add( track );
        m_trackLock.unlock();
        return aggregateTrack.data();
    }
    else
    {
        m_trackLock.unlock();
        m_trackLock.lockForWrite();


        Meta::AggregateTrack *aggregateTrack = new Meta::AggregateTrack( this, track );
        m_trackMap.insert( key, KSharedPtr<Meta::AggregateTrack>( aggregateTrack ) );
        m_trackLock.unlock();
        return aggregateTrack;
    }
}
