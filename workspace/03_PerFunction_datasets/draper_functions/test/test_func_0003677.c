amdlibFreeRegions(amdlibREGION *regions[], int nbRegions )
{
    amdlibREGION *regionTab;

    amdlibLogTrace("amdlibFreeRegions()");


    if (*regions != NULL)
    {
        int i;
        regionTab = *regions;
        for (i = 0; i < nbRegions; i++)
        {
            if (regionTab[i].data != NULL)
            {
                free(regionTab[i].data);
                regionTab[i].data = NULL;
            }
        }
        free(*regions);
        *regions = NULL;
    }
}
