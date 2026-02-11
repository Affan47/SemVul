GDALComputeRasterMinMax( GDALRasterBandH hBand, int bApproxOK,
                         double adfMinMax[2] )

{
    VALIDATE_POINTER0( hBand, "GDALComputeRasterMinMax" );

    GDALRasterBand *poBand = static_cast<GDALRasterBand*>(hBand);
    poBand->ComputeRasterMinMax( bApproxOK, adfMinMax );
}
