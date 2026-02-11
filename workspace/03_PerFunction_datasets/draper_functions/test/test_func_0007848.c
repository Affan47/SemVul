findSmallestTrack( const PerProviderTrackList &providerTracks )
{
    TrackPtr smallest;
    foreach( const TrackList &list, providerTracks )
    {
        if( !smallest || list.first()->lessThan( *smallest, s_comparisonFields ) )
            smallest = list.first();
    }
    Q_ASSERT( smallest );
    return smallest;
}
