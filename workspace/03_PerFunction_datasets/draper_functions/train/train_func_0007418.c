setRating( int newRating )
{
    foreach( Meta::TrackPtr track, m_tracks )
    {
        track->statistics()->setRating( newRating );
    }
}
