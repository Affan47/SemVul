CPLFindLocalXSD(const char* pszXSDFilename)
{
    const char *pszSchemasOpenGIS;
    CPLString osTmp;

    pszSchemasOpenGIS = CPLGetConfigOption("GDAL_OPENGIS_SCHEMAS", NULL);
    if (pszSchemasOpenGIS != NULL)
    {
        int nLen = (int)strlen(pszSchemasOpenGIS);
        if (nLen > 0 && pszSchemasOpenGIS[nLen-1] == '/')
        {
            osTmp = pszSchemasOpenGIS;
            osTmp += pszXSDFilename;
        }
        else
        {
            osTmp = pszSchemasOpenGIS;
            osTmp += "/";
            osTmp += pszXSDFilename;
        }
    }
    else if ((pszSchemasOpenGIS = CPLFindFile( "gdal", "SCHEMAS_OPENGIS_NET" )) != NULL)
    {
        osTmp = pszSchemasOpenGIS;
        osTmp += "/";
        osTmp += pszXSDFilename;
    }

    VSIStatBufL sStatBuf;
    if( VSIStatExL(osTmp, &sStatBuf, VSI_STAT_EXISTS_FLAG) == 0 )
        return osTmp;
    return "";
}
