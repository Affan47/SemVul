CreateSpatialIndex( int nMaxDepth )

{
    if (!TouchLayer())
        return OGRERR_FAILURE;


    if( CheckForQIX() )
        DropSpatialIndex();

    bCheckedForQIX = FALSE;


    SHPTree	*psTree;

    SyncToDisk();
    psTree = SHPCreateTree( hSHP, 2, nMaxDepth, NULL, NULL );

    if( NULL == psTree )
    {


        CPLDebug( "SHAPE",
                  "Index creation failure. Likely, memory allocation error." );

        return OGRERR_FAILURE;
    }


    SHPTreeTrimExtraNodes( psTree );


    char *pszQIXFilename;

    pszQIXFilename = CPLStrdup(CPLResetExtension( pszFullName, "qix" ));

    CPLDebug( "SHAPE", "Creating index file %s", pszQIXFilename );

    SHPWriteTree( psTree, pszQIXFilename );
    CPLFree( pszQIXFilename );


    SHPDestroyTree( psTree );

    CheckForQIX();

    return OGRERR_NONE;
}
