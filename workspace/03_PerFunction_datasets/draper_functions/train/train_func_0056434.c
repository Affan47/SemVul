GetOverviewCount()

{
    if( poDS != NULL && poDS->oOvManager.IsInitialized() )
        return poDS->oOvManager.GetOverviewCount( nBand );
    else
        return 0;
}
