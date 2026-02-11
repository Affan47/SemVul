GDALSerializeGCPTransformer( void *pTransformArg )

{
    CPLXMLNode *psTree;
    GCPTransformInfo *psInfo = (GCPTransformInfo *) pTransformArg;

    VALIDATE_POINTER1( pTransformArg, "GDALSerializeGCPTransformer", NULL );

    psTree = CPLCreateXMLNode( NULL, CXT_Element, "GCPTransformer" );


    CPLCreateXMLElementAndValue(
        psTree, "Order",
        CPLSPrintf( "%d", psInfo->nOrder ) );

    CPLCreateXMLElementAndValue(
        psTree, "Reversed",
        CPLSPrintf( "%d", psInfo->bReversed ) );

    if( psInfo->bRefine )
    {
        CPLCreateXMLElementAndValue(
            psTree, "Refine",
            CPLSPrintf( "%d", psInfo->bRefine ) );

        CPLCreateXMLElementAndValue(
            psTree, "MinimumGcps",
            CPLSPrintf( "%d", psInfo->nMinimumGcps ) );

        CPLCreateXMLElementAndValue(
            psTree, "Tolerance",
            CPLSPrintf( "%f", psInfo->dfTolerance ) );
    }


    if( psInfo->nGCPCount > 0 )
    {
        int iGCP;
        CPLXMLNode *psGCPList = CPLCreateXMLNode( psTree, CXT_Element,
                                                  "GCPList" );

	if(psInfo->bRefine)
	{
	  remove_outliers(psInfo);
	}

        for( iGCP = 0; iGCP < psInfo->nGCPCount; iGCP++ )
        {
            CPLXMLNode *psXMLGCP;
            GDAL_GCP *psGCP = psInfo->pasGCPList + iGCP;

            psXMLGCP = CPLCreateXMLNode( psGCPList, CXT_Element, "GCP" );

            CPLSetXMLValue( psXMLGCP, "#Id", psGCP->pszId );

            if( psGCP->pszInfo != NULL && strlen(psGCP->pszInfo) > 0 )
                CPLSetXMLValue( psXMLGCP, "Info", psGCP->pszInfo );

            CPLSetXMLValue( psXMLGCP, "#Pixel",
                            CPLSPrintf( "%.4f", psGCP->dfGCPPixel ) );

            CPLSetXMLValue( psXMLGCP, "#Line",
                            CPLSPrintf( "%.4f", psGCP->dfGCPLine ) );

            CPLSetXMLValue( psXMLGCP, "#X",
                            CPLSPrintf( "%.12E", psGCP->dfGCPX ) );

            CPLSetXMLValue( psXMLGCP, "#Y",
                            CPLSPrintf( "%.12E", psGCP->dfGCPY ) );

            if( psGCP->dfGCPZ != 0.0 )
                CPLSetXMLValue( psXMLGCP, "#GCPZ",
                                CPLSPrintf( "%.12E", psGCP->dfGCPZ ) );
        }
    }

    return psTree;
}
