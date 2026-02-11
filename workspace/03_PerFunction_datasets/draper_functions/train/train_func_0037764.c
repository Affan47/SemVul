WriteOGRDataSource(const char* pszOGRDataSource,
                                      const char* pszOGRDisplayField,
                                      const char* pszOGRDisplayLayerNames,
                                      const char* pszOGRLinkField,
                                      int bWriteOGRAttributes)
{
    if (OGRGetDriverCount() == 0)
        OGRRegisterAll();

    OGRDataSourceH hDS = OGROpen(pszOGRDataSource, 0, NULL);
    if (hDS == NULL)
        return FALSE;

    int iObj = 0;

    int nLayers = OGR_DS_GetLayerCount(hDS);

    char** papszLayerNames = CSLTokenizeString2(pszOGRDisplayLayerNames,",",0);

    for(int iLayer = 0; iLayer < nLayers; iLayer ++)
    {
        CPLString osLayerName;
        if (CSLCount(papszLayerNames) < nLayers)
            osLayerName = OGR_L_GetName(OGR_DS_GetLayer(hDS, iLayer));
        else
            osLayerName = papszLayerNames[iLayer];

        WriteOGRLayer(hDS, iLayer,
                      pszOGRDisplayField,
                      pszOGRLinkField,
                      osLayerName,
                      bWriteOGRAttributes,
                      iObj);
    }

    OGRReleaseDataSource(hDS);

    CSLDestroy(papszLayerNames);

    return TRUE;
}
