LoadConfigFromXML()
{
    FILE *fp;
    int  nXMLSize;
    char *pszRawXML;

    CPLAssert( poINDFile == NULL );


    fp = VSIFOpen( pszMetadataFilename, "rb" );
    if( fp == NULL )
        return OGRERR_NONE;

    VSIFSeek( fp, 0, SEEK_END );
    nXMLSize = VSIFTell( fp );
    VSIFSeek( fp, 0, SEEK_SET );

    pszRawXML = (char *) CPLMalloc(nXMLSize+1);
    pszRawXML[nXMLSize] = '\0';
    VSIFRead( pszRawXML, nXMLSize, 1, fp );

    VSIFClose( fp );

    OGRErr eErr = LoadConfigFromXML(pszRawXML);
    CPLFree(pszRawXML);

    return eErr;
}
