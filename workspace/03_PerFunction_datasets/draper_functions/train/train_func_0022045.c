Open( GDALOpenInfo * poOpenInfo )

{
    const char *pszFilename = poOpenInfo->pszFilename;
    CPLString osProduct, osDiscId;

    if( !Identify( poOpenInfo ) )
        return NULL;

    if( EQUALN(pszFilename, "ECRG_TOC_ENTRY:",strlen("ECRG_TOC_ENTRY:")))
    {
        pszFilename += strlen("ECRG_TOC_ENTRY:");
        osProduct = pszFilename;
        size_t iPos = osProduct.find(":");
        if (iPos == std::string::npos)
            return NULL;
        osProduct.resize(iPos);

        pszFilename += iPos + 1;
        osDiscId = pszFilename;
        iPos = osDiscId.find(":");
        if (iPos == std::string::npos)
            return NULL;
        osDiscId.resize(iPos);

        pszFilename += iPos + 1;
    }


    CPLXMLNode* psXML = CPLParseXMLFile(pszFilename);
    if (psXML == NULL)
    {
        return NULL;
    }

    GDALDataset* poDS = Build( pszFilename, psXML, osProduct, osDiscId,
                               poOpenInfo->pszFilename);
    CPLDestroyXMLNode(psXML);

    if (poDS && poOpenInfo->eAccess == GA_Update)
    {
        CPLError(CE_Failure, CPLE_NotSupported,
                 "ECRGTOC driver does not support update mode");
        delete poDS;
        return NULL;
    }

    return poDS;
}
