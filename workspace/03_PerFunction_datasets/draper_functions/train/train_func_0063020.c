ensCacheRemove(EnsPCache cache, const void *key)
{
    CachePNode node = NULL;

    if (!cache)
        return ajFalse;

    if (!key)
        return ajFalse;

    node = (CachePNode) ajTableFetchmodV(cache->Table, key);

    if (node)
    {
        cacheNodeRemove(cache, node);


        cacheNodeDel(cache, &node);
    }

    return ajTrue;
}
