value( const Meta::TrackList &tracks ) const
{
    QSet<Meta::AlbumPtr> albums;
    foreach( const Meta::TrackPtr &track, tracks )
    {
        if( track->album() )
            albums.insert( track->album() );
    }
    return QString::number( albums.count() );
}
