Identify( GDALOpenInfo * poOpenInfo )
{
    const char* pszFilename =
        GDALClientDatasetGetFilename(poOpenInfo->pszFilename);
    if( pszFilename == NULL )
        return FALSE;

    CLIENT_ENTER();

    GDALServerSpawnedProcess* ssp = GDALServerSpawnAsync();
    if( ssp == NULL )
        return FALSE;

    char* pszCWD = CPLGetCurrentDir();

    GDALPipe* p = ssp->p;
    if( !GDALPipeWrite(p, INSTR_Identify) ||
        !GDALPipeWrite(p, pszFilename) ||
        !GDALPipeWrite(p, pszCWD) ||
        !GDALSkipUntilEndOfJunkMarker(p) )
    {
        GDALServerSpawnAsyncFinish(ssp);
        CPLFree(pszCWD);
        return FALSE;
    }

    CPLFree(pszCWD);

    int bRet;
    if( !GDALPipeRead(p, &bRet) )
    {
        GDALServerSpawnAsyncFinish(ssp);
        return FALSE;
    }

    GDALServerSpawnAsyncFinish(ssp);
    return bRet;
}
