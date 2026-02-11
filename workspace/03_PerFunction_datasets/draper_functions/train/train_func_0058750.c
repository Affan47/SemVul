Open( const char * pszFilename, int bUpdateIn)

{
    if (bUpdateIn)
    {
        return FALSE;
    }

    pszName = CPLStrdup( pszFilename );

    VSILFILE* fp = VSIFOpenL(pszFilename, "rb");
    if (fp == NULL)
        return FALSE;

    const char* pszLine;
    CPLPushErrorHandler(CPLQuietErrorHandler);
    pszLine = CPLReadLine2L(fp,81,NULL);
    CPLPopErrorHandler();
    CPLErrorReset();


    if (pszLine == NULL || pszLine[0] != 'H')
    {
        VSIFCloseL(fp);
        return FALSE;
    }


    if (strncmp(pszLine, "H0100 ", 6) == 0)
    {
        VSIFSeekL( fp, 0, SEEK_SET );

        VSILFILE* fp2 = VSIFOpenL(pszFilename, "rb");
        if (fp2 == NULL)
        {
            VSIFCloseL(fp);
            return FALSE;
        }

        nLayers = 2;
        papoLayers = (OGRLayer**) CPLMalloc(2 * sizeof(OGRLayer*));
        papoLayers[0] = new OGRUKOOAP190Layer(pszName, fp);
        papoLayers[1] = new OGRSEGUKOOALineLayer(pszName,
                                         new OGRUKOOAP190Layer(pszName, fp2));

        return TRUE;
    }


    for(int iLine = 0; iLine < 21; iLine ++)
    {
        const char* szPtr = pszLine;
        for(;*szPtr != '\0';szPtr++)
        {
            if (*szPtr != 9 && *szPtr < 32)
            {
                VSIFCloseL(fp);
                return FALSE;
            }
        }

        if (iLine == 20)
            break;

        CPLPushErrorHandler(CPLQuietErrorHandler);
        pszLine = CPLReadLine2L(fp,81,NULL);
        CPLPopErrorHandler();
        CPLErrorReset();
        if (pszLine == NULL)
        {
            VSIFCloseL(fp);
            return FALSE;
        }
    }

    char* pszExpandedLine = OGRSEGP1Layer::ExpandTabs(pszLine);
    int nLatitudeCol = OGRSEGP1Layer::DetectLatitudeColumn(pszExpandedLine);
    CPLFree(pszExpandedLine);

    if (nLatitudeCol > 0)
    {
        VSIFSeekL( fp, 0, SEEK_SET );

        VSILFILE* fp2 = VSIFOpenL(pszFilename, "rb");
        if (fp2 == NULL)
        {
            VSIFCloseL(fp);
            return FALSE;
        }

        nLayers = 2;
        papoLayers = (OGRLayer**) CPLMalloc(2 * sizeof(OGRLayer*));
        papoLayers[0] = new OGRSEGP1Layer(pszName, fp, nLatitudeCol);
        papoLayers[1] = new OGRSEGUKOOALineLayer(pszName,
                                         new OGRSEGP1Layer(pszName, fp2,
                                                           nLatitudeCol));

        return TRUE;
    }

    VSIFCloseL(fp);
    return FALSE;
}
