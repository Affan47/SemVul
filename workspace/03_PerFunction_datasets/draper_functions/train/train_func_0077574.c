partForItem( const QModelIndex &index ) const
{
    switch ( index.data( GroupRole ).toInt() )
    {
        case Grouping::Head:
        case Grouping::Body:
        case Grouping::Tail:
        {
            Meta::TrackPtr track = index.data( TrackRole ).value<Meta::TrackPtr>();

            if( !track->artist() || !track->album() || !track->album()->albumArtist() || ( track->artist()->name() != track->album()->albumArtist()->name() ) )
                return VariousArtistsBody;
            else
                return StandardBody;
        }

        case Grouping::None:
        default:
            return Single;
    }
}
