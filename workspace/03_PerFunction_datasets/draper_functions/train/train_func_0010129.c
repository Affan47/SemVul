mCreateCopy( const char* pszFilename,
                                    GDALDataset* poSrcDS,
                                    int bStrict, char** papszOptions,
                                    GDALProgressFunc pfnProgress,
                                    void * pProgressData )
{


    const char* pszServerDriver =
        CSLFetchNameValue(papszOptions, "SERVER_DRIVER");
    if( pszServerDriver == NULL )
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                 "Creation options should contain a SERVER_DRIVER item");
        return FALSE;
    }

    if( !CSLFetchBoolean(papszOptions, "APPEND_SUBDATASET", FALSE) )
    {
        if( !GDALClientDatasetQuietDelete(p, pszFilename) )
            return FALSE;
    }

    GDALPipeWriteConfigOption(p, "GTIFF_POINT_GEO_IGNORE", bRecycleChild);
    GDALPipeWriteConfigOption(p, "GTIFF_DELETE_ON_ERROR", bRecycleChild);
    GDALPipeWriteConfigOption(p, "ESRI_XML_PAM", bRecycleChild);
    GDALPipeWriteConfigOption(p, "GDAL_TIFF_INTERNAL_MASK_TO_8BIT", bRecycleChild);
    GDALPipeWriteConfigOption(p, "OGR_SQLITE_SYNCHRONOUS", bRecycleChild);
    GDALPipeWriteConfigOption(p, "GDAL_PDF_WRITE_GEOREF_ON_IMAGE", bRecycleChild);
    GDALPipeWriteConfigOption(p, "GDAL_PDF_OGC_BP_WRITE_WKT", bRecycleChild);

    char* pszCWD = CPLGetCurrentDir();

    if( !GDALPipeWrite(p, INSTR_CreateCopy) ||
        !GDALPipeWrite(p, pszFilename) ||
        !GDALPipeWrite(p, poSrcDS->GetDescription()) ||
        !GDALPipeWrite(p, pszCWD) ||
        !GDALPipeWrite(p, bStrict) ||
        !GDALPipeWrite(p, papszOptions) )
    {
        CPLFree(pszCWD);
        return FALSE;
    }
    CPLFree(pszCWD);

    int bDriverOK;
    if( !GDALPipeRead(p, &bDriverOK) )
        return FALSE;

    if( !bDriverOK )
    {
        GDALConsumeErrors(p);
        return FALSE;
    }

    if( GDALServerLoop(p,
                       poSrcDS,
                       pfnProgress, pProgressData) != 0 )
    {
        GDALConsumeErrors(p);
        return FALSE;
    }

    GDALConsumeErrors(p);

    return Init(NULL, GA_Update);
}
