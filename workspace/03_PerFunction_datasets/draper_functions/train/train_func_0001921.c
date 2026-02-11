trackMatches( int position,
                                const Meta::TrackList& playlist,
                                int contextCount ) const
{
    foreach( Dynamic::BiasPtr bias, m_biases )
    {
        if( !bias->trackMatches( position, playlist, contextCount ) )
            return false;
    }
    return true;
}
