enableHeader( bool enable )
{
    if( m_header )
    {
        delete m_header;
        m_header = 0;
    }

    if( enable )
    {
        m_header = new AppletHeader( this );
        m_header->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
    }
}
