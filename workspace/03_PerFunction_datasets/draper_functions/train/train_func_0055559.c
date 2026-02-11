slotServiceReady()
{
    while( !m_tracksToLocate.isEmpty() )
    {
        MetaProxy::TrackPtr track = m_tracksToLocate.dequeue();
        if( !track )
            continue;

        track->lookupTrack( this );
    }
}
