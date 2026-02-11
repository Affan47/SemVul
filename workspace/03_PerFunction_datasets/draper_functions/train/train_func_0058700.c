discardRemaining()
{
    m_trackQueue.clear();
    m_currentTrack = TrackInfo();
    abort();

    if ( type() == Type_Station && The::radio().isPlaying() )
    {
        requestPlaylistChunk();
    }
}
