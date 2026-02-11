PlaybackStatus() const
{
    if( The::engineController()->isPlaying() )
        return QLatin1String( "Playing" );
    else if ( The::engineController()->isPaused() )
        return QLatin1String( "Paused" );
    else
        return QLatin1String( "Stopped" );
}
