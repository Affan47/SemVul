onTrackEndReached( int atPosition )
{
    LOGL( 4, "AudioController::onTrackEndReached" );

    emit trackEnded( m_currentTrack, atPosition );
}
