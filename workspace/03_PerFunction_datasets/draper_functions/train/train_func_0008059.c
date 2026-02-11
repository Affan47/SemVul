GDALDeserializeGCPTransformer( CPLXMLNode *psTree )

{
    GDAL_GCP *pasGCPList = 0;
    int nGCPCount = 0;
    void *pResult;
    int nReqOrder;
    int bReversed;
    int bRefine;
    int nMinimumGcps;
    double dfTolerance;


    CPLXMLNode *psGCPList = CPLGetXMLNode( psTree, "GCPList" );

    if( psGCPList != NULL )
    {
        int  nGCPMax = 0;
        CPLXMLNode *psXMLGCP;


        for( psXMLGCP = psGCPList->psChild; psXMLGCP != NULL;
             psXMLGCP = psXMLGCP->psNext )
            nGCPMax++;

        pasGCPList = (GDAL_GCP *) CPLCalloc(sizeof(GDAL_GCP),nGCPMax);

        for( psXMLGCP = psGCPList->psChild; psXMLGCP != NULL;
             psXMLGCP = psXMLGCP->psNext )
        {
            GDAL_GCP *psGCP = pasGCPList + nGCPCount;

            if( !EQUAL(psXMLGCP->pszValue,"GCP") ||
                psXMLGCP->eType != CXT_Element )
                continue;

            GDALInitGCPs( 1, psGCP );

            CPLFree( psGCP->pszId );
            psGCP->pszId = CPLStrdup(CPLGetXMLValue(psXMLGCP,"Id",""));

            CPLFree( psGCP->pszInfo );
            psGCP->pszInfo = CPLStrdup(CPLGetXMLValue(psXMLGCP,"Info",""));

            psGCP->dfGCPPixel = atof(CPLGetXMLValue(psXMLGCP,"Pixel","0.0"));
            psGCP->dfGCPLine = atof(CPLGetXMLValue(psXMLGCP,"Line","0.0"));

            psGCP->dfGCPX = atof(CPLGetXMLValue(psXMLGCP,"X","0.0"));
            psGCP->dfGCPY = atof(CPLGetXMLValue(psXMLGCP,"Y","0.0"));
            psGCP->dfGCPZ = atof(CPLGetXMLValue(psXMLGCP,"Z","0.0"));
            nGCPCount++;
        }
    }


    nReqOrder = atoi(CPLGetXMLValue(psTree,"Order","3"));
    bReversed = atoi(CPLGetXMLValue(psTree,"Reversed","0"));
    bRefine = atoi(CPLGetXMLValue(psTree,"Refine","0"));
    nMinimumGcps = atoi(CPLGetXMLValue(psTree,"MinimumGcps","6"));
    dfTolerance = atof(CPLGetXMLValue(psTree,"Tolerance","1.0"));


    if(bRefine)
    {
        pResult = GDALCreateGCPRefineTransformer( nGCPCount, pasGCPList, nReqOrder,
                                        bReversed, dfTolerance, nMinimumGcps );
    }
    else
    {
        pResult = GDALCreateGCPTransformer( nGCPCount, pasGCPList, nReqOrder,
                                        bReversed );
    }


    GDALDeinitGCPs( nGCPCount, pasGCPList );
    CPLFree( pasGCPList );

    return pResult;
}
