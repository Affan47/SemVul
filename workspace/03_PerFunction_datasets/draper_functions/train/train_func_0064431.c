EstablishOverviews()

{
    if( nOverviews != -1 )
        return;

    nOverviews = HFAGetOverviewCount( hHFA, nBand );
    if( nOverviews > 0 )
    {
        papoOverviewBands = (HFARasterBand **)
            CPLMalloc(sizeof(void*)*nOverviews);

        for( int iOvIndex = 0; iOvIndex < nOverviews; iOvIndex++ )
        {
            papoOverviewBands[iOvIndex] =
                new HFARasterBand( (HFADataset *) poDS, nBand, iOvIndex );
            if (papoOverviewBands[iOvIndex]->GetXSize() == 0)
            {
                delete papoOverviewBands[iOvIndex];
                papoOverviewBands[iOvIndex] = NULL;
            }
        }
    }
}
