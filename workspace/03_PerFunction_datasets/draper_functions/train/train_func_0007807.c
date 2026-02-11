SetGCPs( int nNewCount, const GDAL_GCP *pasNewGCPList,
                            const char *pszGCPProjection )

{
    GDALDeinitGCPs( nGCPCount, pasGCPs );
    CPLFree( pasGCPs );

    if( pszGCPProjection == NULL )
        osGCPProjection = "";
    else
        osGCPProjection = pszGCPProjection;

    nGCPCount = nNewCount;
    pasGCPs = GDALDuplicateGCPs( nGCPCount, pasNewGCPList );

    return CE_None;
}
