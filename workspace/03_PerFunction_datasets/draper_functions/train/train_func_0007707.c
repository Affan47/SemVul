tradindexed_groupadd(const char *group, ARTNUM low, ARTNUM high, char *flag)
{
    if (tradindexed == NULL || tradindexed->index == NULL) {
        warn("tradindexed: overview method not initialized");
        return false;
    }
    return tdx_index_add(tradindexed->index, group, low, high, flag);
}
