addTrack( const QDateTime &recentlyPlayed,
                                         const QString &displayName,
                                         const QString &trackUrl )
{
    while( m_recentTracks.size() >= 10 )
    {

        RecentlyPlayedTrackData data = m_recentTracks.dequeue();
        delete data.widget;
    }

    RecentlyPlayedTrackData data;
    data.recentlyPlayed = recentlyPlayed;
    data.displayName = displayName;
    data.trackUrl = trackUrl;
    data.widget = addWidgetItem( data );
    m_recentTracks.enqueue( data );
}
