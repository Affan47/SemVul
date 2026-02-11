SetBand( int nNewBand, GDALRasterBand * poBand )

{


    if( nBands < nNewBand || papoBands == NULL ) {
        int             i;
        GDALRasterBand** papoNewBands;

        if( papoBands == NULL )
            papoNewBands = (GDALRasterBand **)
                VSICalloc(sizeof(GDALRasterBand*), MAX(nNewBand,nBands));
        else
            papoNewBands = (GDALRasterBand **)
                VSIRealloc(papoBands, sizeof(GDALRasterBand*) *
                           MAX(nNewBand,nBands));
        if (papoNewBands == NULL)
        {
            ReportError(CE_Failure, CPLE_OutOfMemory,
                     "Cannot allocate band array");
            return;
        }
        papoBands = papoNewBands;

        for( i = nBands; i < nNewBand; i++ )
            papoBands[i] = NULL;

        nBands = MAX(nBands,nNewBand);
    }


    if( papoBands[nNewBand-1] != NULL )
    {
        ReportError(CE_Failure, CPLE_NotSupported,
                 "Cannot set band %d as it is already set", nNewBand);
        return;
    }

    papoBands[nNewBand-1] = poBand;


    poBand->nBand = nNewBand;
    poBand->poDS = this;
    poBand->nRasterXSize = nRasterXSize;
    poBand->nRasterYSize = nRasterYSize;
    poBand->eAccess = eAccess;
}
