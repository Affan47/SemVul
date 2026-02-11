hasConflict( int i ) const
{
    if( i >= 0 )
        return m_matchedTuples.value( i ).hasConflict( m_options );
    foreach( const TrackTuple &tuple, m_matchedTuples )
    {
        if( tuple.hasConflict( m_options ) )
            return true;
    }
    return false;
}
