GDALDatasetAdviseRead( GDALDatasetH hDS,
                       int nXOff, int nYOff, int nXSize, int nYSize,
                       int nBufXSize, int nBufYSize, GDALDataType eDT,
                       int nBandCount, int *panBandMap,char **papszOptions )

{
    VALIDATE_POINTER1( hDS, "GDALDatasetAdviseRead", CE_Failure );

    return ((GDALDataset *) hDS)->AdviseRead( nXOff, nYOff, nXSize, nYSize,
                                              nBufXSize, nBufYSize, eDT,
                                              nBandCount, panBandMap,
                                              papszOptions );
}
