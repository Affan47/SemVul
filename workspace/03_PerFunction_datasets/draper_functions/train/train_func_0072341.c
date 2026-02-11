GTIFFSetJpegQuality(GDALDatasetH hGTIFFDS, int nJpegQuality)
{
    CPLAssert(EQUAL(GDALGetDriverShortName(GDALGetDatasetDriver(hGTIFFDS)), "GTIFF"));

    GTiffDataset* poDS = (GTiffDataset*)hGTIFFDS;
    poDS->nJpegQuality = nJpegQuality;

    poDS->ScanDirectories();

    int i;
    for(i=0;i<poDS->nOverviewCount;i++)
        poDS->papoOverviewDS[i]->nJpegQuality = nJpegQuality;
}
