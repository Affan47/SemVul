textForScrobblableStatus( TrackInfo& track )
{
    QString text = tr( "Can't scrobble: %1" );
    switch ( MooseUtils::scrobblableStatus( track ) )
    {
        case MooseEnums::ArtistNameMissing:
        case MooseEnums::TrackNameMissing:
            return text.arg( tr( "artist or title missing from ID3 tag" ) );

        case MooseEnums::TooShort: return text.arg( tr( "track too short" ) );
        case MooseEnums::ExcludedDir: return tr( "Won't scrobble: track is in directory set to not scrobble" );
        case MooseEnums::ArtistInvalid: return text.arg( tr( "invalid artist name" ) );

        case Moose::NoTimeStamp:
        case Moose::FromTheFuture:
        case Moose::FromTheDistantPast:
            return text.arg( tr( "invalid start time" ) );

        case Moose::OkToScrobble:
            if ( track.isPowerPlay() )
                return tr( "%1 (Brought to you by %2)" ).arg( track.toString() ).arg( track.powerPlayLabel() );

            return track.toString();

        default:
            Q_ASSERT( !"Unhandled Enum Value!" );
            return track.toString();
    }
}
