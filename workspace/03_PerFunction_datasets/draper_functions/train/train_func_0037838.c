BuildPolygons()
{
    int iter;
    for(iter=0;iter<(int)listFEA_PFE.size();iter++)
    {
        const CPLString& osFEA = listFEA_PFE[iter].first;
        const CPLString& osPFE = listFEA_PFE[iter].second;
        BuildPolygon(osFEA, osPFE);
    }

    return TRUE;
}
