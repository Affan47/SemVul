trackAt( int row ) const
{
    if ( rowExists( row ) )
        return m_items.at( row )->track();
    else
        return Meta::TrackPtr();
}
