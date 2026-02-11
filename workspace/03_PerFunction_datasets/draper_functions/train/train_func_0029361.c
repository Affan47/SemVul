tradindexed_groupstats(const char *group, int *low, int *high, int *count,
                       int *flag)
{
    const struct group_entry *entry;

    if (tradindexed == NULL || tradindexed->index == NULL) {
        warn("tradindexed: overview method not initialized");
        return false;
    }
    entry = tdx_index_entry(tradindexed->index, group);
    if (entry == NULL)
        return false;
    if (low != NULL)
        *low = entry->low;
    if (high != NULL)
        *high = entry->high;
    if (count != NULL)
        *count = entry->count;
    if (flag != NULL)
        *flag = entry->flag;
    return true;
}
