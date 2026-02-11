handleResult( const Meta::TrackList &tracks )
{
    Meta::TrackList ret;
    if( m_convertToMultiTracks )
    {
        foreach( const Meta::TrackPtr &track, tracks )
        {
            using namespace Meta;
            const ScriptableServiceTrack *serviceTrack =
                    dynamic_cast<const ScriptableServiceTrack *>( track.data() );
            if( !serviceTrack )
            {
                error() << "failed to convert generic track" << track.data() << "to ScriptableServiceTrack";
                continue;
            }
            ret << serviceTrack->playableTrack();
        }
    }
    else
        ret = tracks;

    if ( d->maxsize >= 0 && ret.count() > d->maxsize )
        emit newResultReady( ret.mid( 0, d->maxsize ) );
    else
        emit newResultReady( ret );
}
