setTagsToMultipleTracks( QVariantMap tags )
{
    tags.remove( Meta::Field::LABELS );

    foreach( const Meta::TrackPtr &track, m_tracks )
    {
        setTagsToTrack( track, tags );
    }
}
