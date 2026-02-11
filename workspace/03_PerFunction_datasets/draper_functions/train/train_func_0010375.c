itemAt( const QPoint& pos )
{
    for ( int i = 0; i < m_hfwLayout.size(); ++i )
    {
        const QRect& itemRect = m_hfwLayout.at( i );
        if ( itemRect.contains( pos ) )
        {
            return i;
        }
    }
    return -1;
}
