onTrackEnded( const TrackInfo& track, int at )
{
    Q_UNUSED( at )

    m_trackWatch.stop();
    m_trackWatch.reset();
    m_stationWatch.stop();

    LOGL( 4, "Radio sending stop for " << track.toString() << " to listener." );

    CPlayerListener& listener = The::app().listener();
    CPlayerCommand cmd( PCMD_STOP, MooseConstants::kRadioPluginId, track );
    listener.Handle( cmd );

    if ( m_handshakeAfterNext )
    {
        m_audioController.stop();
        m_handshakeAfterNext = false;
        reHandshake();
    }
}
