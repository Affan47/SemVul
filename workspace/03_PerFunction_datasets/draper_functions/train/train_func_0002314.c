GDALComputeRasterStatistics(
        GDALRasterBandH hBand, int bApproxOK,
        double *pdfMin, double *pdfMax, double *pdfMean, double *pdfStdDev,
        GDALProgressFunc pfnProgress, void *pProgressData )

{
    VALIDATE_POINTER1( hBand, "GDALComputeRasterStatistics", CE_Failure );

    GDALRasterBand *poBand = static_cast<GDALRasterBand*>(hBand);

    return poBand->ComputeStatistics(
        bApproxOK, pdfMin, pdfMax, pdfMean, pdfStdDev,
        pfnProgress, pProgressData );
}
