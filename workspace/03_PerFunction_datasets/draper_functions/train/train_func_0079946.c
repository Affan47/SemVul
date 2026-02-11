find( const Meta::TrackList& tl ) const
{
    QList<int> positions;
    for ( int i = 0; i < tl.length(); i++ ) {
        if ( tl.at( i )->artist() == m_artistToMatch ) {
            positions << i;
        }
    }

    return positions;
}
