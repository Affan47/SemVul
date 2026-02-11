cacheNodeRemove(EnsPCache cache, const CachePNode node)
{
    AjIList iter = NULL;

    CachePNode lnode = NULL;

    if (!cache)
        return ajFalse;

    if (!node)
        return ajFalse;


    iter = ajListIterNew(cache->List);

    while (!ajListIterDone(iter))
    {
        lnode = (CachePNode) ajListIterGet(iter);

        if (lnode == node)
        {
            ajListIterRemove(iter);

            break;
        }
    }

    ajListIterDel(&iter);


    ajTableRemove(cache->Table, node->Key);


    cache->Bytes -= node->Bytes;

    cache->Count--;

    cache->Removed++;

    return ajTrue;
}
