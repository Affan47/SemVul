InitCache(uint uCacheCount, tree_t *tree)
{
    uint uNodeIndex;

    tree->m_uCacheCount = uCacheCount;

    tree->m_uNeighbor1 = (uint *) CKMALLOC(sizeof(uint) * tree->m_uCacheCount);
    tree->m_uNeighbor2 = (uint *) CKMALLOC(sizeof(uint) * tree->m_uCacheCount);
    tree->m_uNeighbor3 = (uint *) CKMALLOC(sizeof(uint) * tree->m_uCacheCount);

    tree->m_Ids = (uint *) CKMALLOC(sizeof(uint) * tree->m_uCacheCount);

    tree->m_dEdgeLength1 = (double *) CKMALLOC(sizeof(double) * tree->m_uCacheCount);
    tree->m_dEdgeLength2 = (double *) CKMALLOC(sizeof(double) * tree->m_uCacheCount);
    tree->m_dEdgeLength3 = (double *) CKMALLOC(sizeof(double) * tree->m_uCacheCount);
#if USE_HEIGHT
    tree->m_dHeight = (double *) CKMALLOC(sizeof(double) * tree->m_uCacheCount);
    tree->m_bHasHeight = (bool *) CKMALLOC(sizeof(bool) * tree->m_uCacheCount);
#endif
    tree->m_bHasEdgeLength1 = (bool *) CKMALLOC(sizeof(bool) * tree->m_uCacheCount);
    tree->m_bHasEdgeLength2 = (bool *) CKMALLOC(sizeof(bool) * tree->m_uCacheCount);
    tree->m_bHasEdgeLength3 = (bool *) CKMALLOC(sizeof(bool) * tree->m_uCacheCount);

    tree->m_ptrName = (char **) CKMALLOC(sizeof(char *) * tree->m_uCacheCount);

    for (uNodeIndex = 0; uNodeIndex < tree->m_uNodeCount; ++uNodeIndex) {
        InitNode(tree, uNodeIndex);
    }
}
