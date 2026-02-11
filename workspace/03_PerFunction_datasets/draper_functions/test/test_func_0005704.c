RefUnderlyingRasterBand()
{
    poUnderlyingMainRasterBand = poMainBand->RefUnderlyingRasterBand();
    if (poUnderlyingMainRasterBand == NULL)
        return NULL;

    nRefCountUnderlyingMainRasterBand ++;
    return poUnderlyingMainRasterBand->GetOverview(nOverviewBand);
}
