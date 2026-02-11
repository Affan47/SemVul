setEnabled( bool enabled )
{
    m_enabled = enabled;

    if ( !enabled && !m_disabled.isNull() )
        setPixmap( m_disabled );
    else
        setPixmap( m_normal );
}
