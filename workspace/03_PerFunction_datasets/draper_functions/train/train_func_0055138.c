CacheAddByGeomId( int nGeomId, OGRGeometry *poGeometry )

{
    if( !bCacheLines )
        return;

    CPLAssert( nGeomId >= 0 );


    if( nGeomId >= nLineCacheSize )
    {
        int     nNewSize = nGeomId + 100;

        papoLineCache = (OGRGeometry **)
            CPLRealloc( papoLineCache, sizeof(void*) * nNewSize );
        memset( papoLineCache + nLineCacheSize, 0,
                sizeof(void*) * (nNewSize - nLineCacheSize) );
        nLineCacheSize = nNewSize;
    }


    if( papoLineCache[nGeomId] != NULL )
        return;

    papoLineCache[nGeomId] = poGeometry->clone();
}
