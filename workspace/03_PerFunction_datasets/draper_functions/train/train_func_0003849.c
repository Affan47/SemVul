GetOverviewCount()
{
    MBTilesDataset* poGDS = (MBTilesDataset*) poDS;

    if (poGDS->nResolutions >= 1)
        return poGDS->nResolutions;
    else
        return GDALPamRasterBand::GetOverviewCount();
}
