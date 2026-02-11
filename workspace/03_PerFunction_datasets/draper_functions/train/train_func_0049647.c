UnrefUnderlyingDataset(GDALDataset* poUnderlyingDataset)
{
    if (cacheEntry != NULL)
    {
        CPLAssert(cacheEntry->poDS == poUnderlyingDataset);
        if (cacheEntry->poDS != NULL)
            GDALDatasetPool::UnrefDataset(cacheEntry);
    }
}
