LoadClasses( const char *pszFile )

{

    if( pszFile == NULL )
        return FALSE;


    FILE       *fp;
    int         nLength;
    char        *pszWholeText;

    fp = VSIFOpen( pszFile, "rb" );

    if( fp == NULL )
    {
        CPLError( CE_Failure, CPLE_OpenFailed,
                  "Failed to open file %s.", pszFile );
        return FALSE;
    }

    VSIFSeek( fp, 0, SEEK_END );
    nLength = VSIFTell( fp );
    VSIFSeek( fp, 0, SEEK_SET );

    pszWholeText = (char *) VSIMalloc(nLength+1);
    if( pszWholeText == NULL )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Failed to allocate %d byte buffer for %s,\n"
                  "is this really a GMLFeatureClassList file?",
                  nLength, pszFile );
        VSIFClose( fp );
        return FALSE;
    }

    if( VSIFRead( pszWholeText, nLength, 1, fp ) != 1 )
    {
        VSIFree( pszWholeText );
        VSIFClose( fp );
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Read failed on %s.", pszFile );
        return FALSE;
    }
    pszWholeText[nLength] = '\0';

    VSIFClose( fp );

    if( strstr( pszWholeText, "<GMLFeatureClassList>" ) == NULL )
    {
        VSIFree( pszWholeText );
        CPLError( CE_Failure, CPLE_AppDefined,
                  "File %s does not contain a GMLFeatureClassList tree.",
                  pszFile );
        return FALSE;
    }


    CPLXMLNode *psRoot;

    psRoot = CPLParseXMLString( pszWholeText );
    VSIFree( pszWholeText );


    if( psRoot == NULL )
        return FALSE;

    if( psRoot->eType != CXT_Element
        || !EQUAL(psRoot->pszValue,"GMLFeatureClassList") )
    {
        CPLDestroyXMLNode(psRoot);
        CPLError( CE_Failure, CPLE_AppDefined,
                  "File %s is not a GMLFeatureClassList document.",
                  pszFile );
        return FALSE;
    }


    CPLXMLNode *psThis;

    for( psThis = psRoot->psChild; psThis != NULL; psThis = psThis->psNext )
    {
        if( psThis->eType == CXT_Element
            && EQUAL(psThis->pszValue,"GMLFeatureClass") )
        {
            GMLFeatureClass   *poClass;

            poClass = new GMLFeatureClass();

            if( !poClass->InitializeFromXML( psThis ) )
            {
                delete poClass;
                CPLDestroyXMLNode( psRoot );
                return FALSE;
            }

            poClass->SetSchemaLocked( TRUE );

            AddClass( poClass );
        }
    }

    CPLDestroyXMLNode( psRoot );

    SetClassListLocked( TRUE );

    return TRUE;
}
