setSuspended( bool val )
{
    if ( m_state == Suspended && val == false )
    {
        m_clock->start();
        m_board->setPaused( false );
        m_state = Running;
        emit stateChanged( m_state );
    }

    if ( m_state == Running && val == true )
    {
        m_clock->stop();
        m_board->setPaused( true );
        m_state = Suspended;
        emit stateChanged( m_state );
    }
    redraw();
}
