FlushCache()

{
    GDALDataset::FlushCache();

    if ( !bHeaderDirty )
        return;

    if ( eRMFType == RMFT_MTW )
    {
        GDALRasterBand *poBand = GetRasterBand(1);

        if ( poBand )
        {
            poBand->ComputeRasterMinMax( FALSE, sHeader.adfElevMinMax );
            bHeaderDirty = TRUE;
        }
    }
    WriteHeader();
}
