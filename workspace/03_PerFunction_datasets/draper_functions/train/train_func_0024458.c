OGRGeocodeDestroySession(OGRGeocodingSessionH hSession)
{
    if( hSession == NULL )
        return;
    CPLFree(hSession->pszCacheFilename);
    CPLFree(hSession->pszGeocodingService);
    CPLFree(hSession->pszEmail);
    CPLFree(hSession->pszUserName);
    CPLFree(hSession->pszKey);
    CPLFree(hSession->pszApplication);
    CPLFree(hSession->pszLanguage);
    CPLFree(hSession->pszQueryTemplate);
    CPLFree(hSession->pszReverseQueryTemplate);
    if( hSession->poDS )
        OGRReleaseDataSource((OGRDataSourceH) hSession->poDS);
    CPLFree(hSession);
}
