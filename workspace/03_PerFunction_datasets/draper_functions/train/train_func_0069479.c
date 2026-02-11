TrimExcessMemory( void )
{
    bool found = false;
    const std::size_t allocCount = GetOffset( GetMaxObjectSize(), GetAlignment() );
    std::size_t i = 0;
    for ( ; i < allocCount; ++i )
    {
        if ( pool_[ i ].TrimEmptyChunk() )
            found = true;
    }
    for ( i = 0; i < allocCount; ++i )
    {
        if ( pool_[ i ].TrimChunkList() )
            found = true;
    }

    return found;
}
