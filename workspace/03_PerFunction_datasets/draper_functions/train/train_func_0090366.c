GDALSerializeTPSTransformer( void *pTransformArg )

{
    VALIDATE_POINTER1( pTransformArg, "GDALSerializeTPSTransformer", NULL );

    CPLXMLNode *psTree;
    TPSTransformInfo *psInfo = static_cast<TPSTransformInfo *>(pTransformArg);

    psTree = CPLCreateXMLNode( NULL, CXT_Element, "TPSTransformer" );


    CPLCreateXMLElementAndValue(
        psTree, "Reversed",
        CPLString().Printf( "%d", psInfo->bReversed ) );


    if( psInfo->nGCPCount > 0 )
    {
        int iGCP;
        CPLXMLNode *psGCPList = CPLCreateXMLNode( psTree, CXT_Element,
                                                  "GCPList" );

        for( iGCP = 0; iGCP < psInfo->nGCPCount; iGCP++ )
        {
            CPLXMLNode *psXMLGCP;
            GDAL_GCP *psGCP = psInfo->pasGCPList + iGCP;

            psXMLGCP = CPLCreateXMLNode( psGCPList, CXT_Element, "GCP" );

            CPLSetXMLValue( psXMLGCP, "#Id", psGCP->pszId );

            if( psGCP->pszInfo != NULL && strlen(psGCP->pszInfo) > 0 )
                CPLSetXMLValue( psXMLGCP, "Info", psGCP->pszInfo );

            CPLSetXMLValue( psXMLGCP, "#Pixel",
                            CPLString().Printf( "%.4f", psGCP->dfGCPPixel ) );

            CPLSetXMLValue( psXMLGCP, "#Line",
                            CPLString().Printf( "%.4f", psGCP->dfGCPLine ) );

            CPLSetXMLValue( psXMLGCP, "#X",
                            CPLString().Printf( "%.12E", psGCP->dfGCPX ) );

            CPLSetXMLValue( psXMLGCP, "#Y",
                            CPLString().Printf( "%.12E", psGCP->dfGCPY ) );

            if( psGCP->dfGCPZ != 0.0 )
                CPLSetXMLValue( psXMLGCP, "#GCPZ",
                                CPLString().Printf( "%.12E", psGCP->dfGCPZ ) );
        }
    }

    return psTree;
}
