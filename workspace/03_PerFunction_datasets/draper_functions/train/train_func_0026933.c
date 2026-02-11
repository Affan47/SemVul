addTrack( Meta::TrackPtr track, int position )
{
    DEBUG_BLOCK
    int insertAt = (position == -1) ? m_tracks.count() : position;
    m_tracks.insert( insertAt, track );
}
