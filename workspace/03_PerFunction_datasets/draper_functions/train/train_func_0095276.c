Set( const char *pszPath, const char *pszValue )

{
    CPLString  osPath = pszPath;
    int iDot;

    iDot = osPath.find_first_of('.');


    if( iDot != -1 )
    {
        CPLString osPathFirst = osPath.substr(0,iDot);
        CPLString osPathRest = osPath.substr(iDot+1);
        ERSHdrNode *poFirst = FindNode( osPathFirst );

        if( poFirst == NULL )
        {
            poFirst = new ERSHdrNode();

            MakeSpace();
            papszItemName[nItemCount] = CPLStrdup(osPathFirst);
            papszItemValue[nItemCount] = NULL;
            papoItemChild[nItemCount] = poFirst;
            nItemCount++;
        }

        poFirst->Set( osPathRest, pszValue );
        return;
    }


    int i;

    for( i = 0; i < nItemCount; i++ )
    {
        if( EQUAL(osPath,papszItemName[i])
            && papszItemValue[i] != NULL )
        {
            CPLFree( papszItemValue[i] );
            papszItemValue[i] = CPLStrdup( pszValue );
            return;
        }
    }

    MakeSpace();
    papszItemName[nItemCount] = CPLStrdup(osPath);
    papszItemValue[nItemCount] = CPLStrdup(pszValue);
    papoItemChild[nItemCount] = NULL;
    nItemCount++;
}
