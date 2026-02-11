GetOverviewCount( int nBand )

{
    GDALRasterBand * poBand;

    if( poODS == NULL || nBand < 1 || nBand > poODS->GetRasterCount() )
        return 0;

    poBand = poODS->GetRasterBand( nBand );
    if( poBand == NULL )
        return 0;
    else
    {
        if( bOvrIsAux )
            return poBand->GetOverviewCount();
        else
            return poBand->GetOverviewCount() + 1;
    }
}
