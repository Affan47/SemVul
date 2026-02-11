bitrate() const
{
    foreach( const Meta::TrackPtr &track, m_tracks )
    {
        if( track->bitrate() )
            return track->bitrate();
    }
    return 0;
}
