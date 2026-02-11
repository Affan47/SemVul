DownloadGetCapabilities(GDALOpenInfo *poOpenInfo)
{
    const char* pszURL = poOpenInfo->pszFilename;
    if (EQUALN(pszURL, "WMS:", 4))
        pszURL += 4;

    CPLString osFormat = CPLURLGetValue(pszURL, "FORMAT");
    CPLString osTransparent = CPLURLGetValue(pszURL, "TRANSPARENT");
    CPLString osVersion = CPLURLGetValue(pszURL, "VERSION");

    if (osVersion.size() == 0)
        osVersion = "1.1.1";

    CPLString osURL(pszURL);
    osURL = CPLURLAddKVP(osURL, "SERVICE", "WMS");
    osURL = CPLURLAddKVP(osURL, "VERSION", osVersion);
    osURL = CPLURLAddKVP(osURL, "REQUEST", "GetCapabilities");

    osURL = CPLURLAddKVP(osURL, "LAYERS", NULL);
    osURL = CPLURLAddKVP(osURL, "SRS", NULL);
    osURL = CPLURLAddKVP(osURL, "CRS", NULL);
    osURL = CPLURLAddKVP(osURL, "BBOX", NULL);
    osURL = CPLURLAddKVP(osURL, "FORMAT", NULL);
    osURL = CPLURLAddKVP(osURL, "TRANSPARENT", NULL);
    osURL = CPLURLAddKVP(osURL, "STYLES", NULL);
    osURL = CPLURLAddKVP(osURL, "WIDTH", NULL);
    osURL = CPLURLAddKVP(osURL, "HEIGHT", NULL);

    CPLHTTPResult* psResult = CPLHTTPFetch( osURL, NULL );
    if (psResult == NULL)
    {
        return NULL;
    }
    if (psResult->nStatus != 0 || psResult->pszErrBuf != NULL)
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                 "Error returned by server : %s (%d)",
                 (psResult->pszErrBuf) ? psResult->pszErrBuf : "unknown",
                 psResult->nStatus);
        CPLHTTPDestroyResult(psResult);
        return NULL;
    }
    if (psResult->pabyData == NULL)
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                 "Empty content returned by server");
        CPLHTTPDestroyResult(psResult);
        return NULL;
    }

    CPLXMLNode* psXML = CPLParseXMLString( (const char*) psResult->pabyData );
    if (psXML == NULL)
    {
        CPLError(CE_Failure, CPLE_AppDefined, "Invalid XML content : %s",
                psResult->pabyData);
        CPLHTTPDestroyResult(psResult);
        return NULL;
    }

    GDALDataset* poRet = AnalyzeGetCapabilities(psXML, osFormat, osTransparent);

    CPLHTTPDestroyResult(psResult);
    CPLDestroyXMLNode( psXML );

    return poRet;
}
