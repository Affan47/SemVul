GetRegion(const char* pszURL,
                                                        vsi_l_offset nFileOffsetStart)
{
    CPLMutexHolder oHolder( &hMutex );

    unsigned long   pszURLHash = CPLHashSetHashStr(pszURL);

    nFileOffsetStart = (nFileOffsetStart / DOWNLOAD_CHUNCK_SIZE) * DOWNLOAD_CHUNCK_SIZE;
    int i;
    for(i=0;i<nRegions;i++)
    {
        CachedRegion* psRegion = papsRegions[i];
        if (psRegion->pszURLHash == pszURLHash &&
            nFileOffsetStart == psRegion->nFileOffsetStart)
        {
            memmove(papsRegions + 1, papsRegions, i * sizeof(CachedRegion*));
            papsRegions[0] = psRegion;
            return psRegion;
        }
    }
    if (bUseCacheDisk)
        return GetRegionFromCacheDisk(pszURL, nFileOffsetStart);
    return NULL;
}
