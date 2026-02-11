stop()
{
    LOGL( 4, "AudioController requesting stop of " << m_currentTrack.toString() );

    AudioControllerThread::StopEvent* e = new AudioControllerThread::StopEvent();
    QCoreApplication::postEvent( m_thread.eventHandler(), e );

    setState( State_Stopping );
}
