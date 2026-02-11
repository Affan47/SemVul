Close()

{


    if( fpDDF != NULL )
    {
        VSIFCloseL( fpDDF );
        fpDDF = NULL;
    }


    if( poRecord != NULL )
    {
        delete poRecord;
        poRecord = NULL;
    }


    while( nCloneCount > 0 )
        delete papoClones[0];

    nMaxCloneCount = 0;
    CPLFree( papoClones );
    papoClones = NULL;


    int i;

    for( i = 0; i < nFieldDefnCount; i++ )
        delete papoFieldDefns[i];
    CPLFree( papoFieldDefns );
    papoFieldDefns = NULL;
    nFieldDefnCount = 0;
}
