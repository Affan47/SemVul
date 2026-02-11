rowMatch( int sourceModelRow, const QString &searchTerms, int searchFields ) const
{
    if ( !m_belowModel )
        return false;

    Meta::TrackPtr track = m_belowModel->trackAt( sourceModelRow );

    QStringList searchList = searchTerms.split(" ", QString::SkipEmptyParts);

    foreach( const QString& searchTerm, searchList )
    {
        bool match = false;

        if ( searchFields & MatchTrack &&
            track->prettyName().contains( searchTerm, Qt::CaseInsensitive )
        )
            match = true;

        if ( searchFields & MatchArtist &&
            track->artist() &&
            track->artist()->prettyName().contains( searchTerm, Qt::CaseInsensitive )
        )
            match = true;

        if ( searchFields & MatchAlbum &&
            track->album() &&
            track->album()->prettyName().contains( searchTerm, Qt::CaseInsensitive )
        )
            match = true;

        if ( searchFields & MatchGenre &&
            track->genre() &&
            track->genre()->prettyName().contains( searchTerm, Qt::CaseInsensitive )
        )
            match = true;

        if ( searchFields & MatchComposer &&
            track->composer() &&
            track->composer()->prettyName().contains( searchTerm, Qt::CaseInsensitive )
        )
            match = true;

        if ( searchFields & MatchYear &&
            track->year() &&
            track->year()->prettyName().contains( searchTerm, Qt::CaseInsensitive )
        )
            match = true;

        if( searchFields & MatchRating )
        {
            bool ok;
            int rating = QString( searchTerm ).remove( "rating:" ).toInt( &ok );
            if( ok && ( track->statistics()->rating() == rating ) )
                match = true;
        }

        if( !match )
            return false;
    }

    return true;
}
