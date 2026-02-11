findInterval(const BWTIndexSet& indices, const std::string& w)
{
    if(indices.pCache != NULL)
        return findIntervalWithCache(indices.pBWT, indices.pCache, w);
    else
        return findInterval(indices.pBWT, w);
}
