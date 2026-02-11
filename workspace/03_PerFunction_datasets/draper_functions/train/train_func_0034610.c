setSize( const QSize & size )
{
    if ( size != renderSize() )
    {
        setRenderSize( size );
        m_fontCached = false;
    }
}
