stop( )
{
    try{ if( m_start )
             m_rtaudio->stopStream();
         m_start = FALSE;
    } catch( RtError err ){ return FALSE; }

    return !m_start;
}
