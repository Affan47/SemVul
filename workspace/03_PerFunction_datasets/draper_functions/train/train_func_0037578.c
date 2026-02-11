trackList( const Meta::TrackList &tracks ) const
{
    QStringList trackList;
    foreach( Meta::TrackPtr track, tracks )
    {
        QString url = track->prettyUrl();
        Meta::ArtistPtr artist = track->artist();
        QString artistName = artist ? artist->name() : QString();
        QString trackName = track->name();

        QString str;

        if( !trackName.isEmpty() && !artistName.isEmpty() )
            str = i18nc( "%1 is track url, %2 track title, %3 track artist",
                         "%1 (%2 by %3)", url, trackName, artistName );
        else if( !trackName.isEmpty() )
            str = i18nc( "%1 is track url, %2 track name", "%1 (%2)", url, trackName );
        else if( !artistName.isEmpty() )
            str = i18nc( "%1 is track url, %2 artist name", "%1 (by %2)", url, artistName );
        else
            str = url;

        trackList << str;
    }

    return trackList;
}
