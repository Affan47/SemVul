GetMaximum( int *pbSuccess )
{
    FITDataset *poFIT_DS = (FITDataset *) poDS;

    if ((! poFIT_DS) || (! poFIT_DS->info))
        return GDALRasterBand::GetMaximum( pbSuccess );

    if (pbSuccess)
        *pbSuccess = TRUE;

    if (EQUALN((const char *) &poFIT_DS->info->version, "02", 2)) {
        return poFIT_DS->info->maxValue;
    }
    else {
        return GDALRasterBand::GetMaximum( pbSuccess );
    }
}
