setStopAfterCurrent( bool on )
{
    if( on )
        The::playlistActions()->stopAfterPlayingTrack();
    else
        The::playlistActions()->stopAfterPlayingTrack( 0 );
}
