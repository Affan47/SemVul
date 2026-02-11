syncedPlaycount( const Options &options ) const
{
    if( isEmpty() || !(options.syncedFields() & Meta::valPlaycount) )
        return 0;
    int max = 0;
    int sumRecent = 0;
    foreach( TrackPtr track, m_map )
    {
        int recent = track->recentPlayCount();
        sumRecent += recent;
        max = qMax( max, track->playCount() - recent );
    }
    return max + sumRecent;
}
