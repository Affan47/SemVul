trackNumber() const
{
    int result = 0;
    foreach( const Meta::TrackPtr &track, m_tracks )
    {
        if( ( !result && track->trackNumber() ) || ( result && result == track->trackNumber() ) )
        {
            result = track->trackNumber();
        }
        else if( result && result != track->trackNumber() )
        {

            return 0;
        }
    }
    return result;
}
