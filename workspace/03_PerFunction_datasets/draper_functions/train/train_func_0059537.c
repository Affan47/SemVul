GDALDumpOpenDatasets( FILE *fp )

{
    VALIDATE_POINTER1( fp, "GDALDumpOpenDatasets", 0 );

    CPLMutexHolderD( &hDLMutex );

    if (phAllDatasetSet != NULL)
    {
        VSIFPrintf( fp, "Open GDAL Datasets:\n" );
        CPLHashSetForeach(phAllDatasetSet, GDALDumpOpenDatasetsForeach, fp);
        if (phSharedDatasetSet != NULL)
        {
            CPLHashSetForeach(phSharedDatasetSet, GDALDumpOpenSharedDatasetsForeach, fp);
        }
        return CPLHashSetSize(phAllDatasetSet);
    }
    else
    {
        return 0;
    }
}
