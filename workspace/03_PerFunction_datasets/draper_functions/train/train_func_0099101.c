VertexCache_getVertex ( const u32 sourceIndex )
{
	for ( s32 i = 0; i < VERTEXCACHE_ELEMENT; ++i )
	{
		if ( VertexCache.info[ i ].index == sourceIndex )
		{
			return (s4DVertex *) ( (u8*) VertexCache.mem.data + ( i << ( SIZEOF_SVERTEX_LOG2 + 1  ) ) );
		}
	}
	return 0;
}
