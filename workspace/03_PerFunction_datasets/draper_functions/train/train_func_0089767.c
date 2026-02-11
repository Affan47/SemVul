tradindexed_getartinfo(const char *group, ARTNUM artnum, TOKEN *token)
{
    struct group_entry *entry;
    struct group_data *data;
    const struct index_entry *index_entry;

    if (tradindexed == NULL || tradindexed->index == NULL) {
        warn("tradindexed: overview method not initialized");
        return false;
    }
    entry = tdx_index_entry(tradindexed->index, group);
    if (entry == NULL)
        return false;
    data = data_cache_open(tradindexed, group, entry);
    if (data == NULL)
        return false;
    if (entry->base != data->base)
        if (data->base > artnum && entry->base <= artnum) {
            data = data_cache_reopen(tradindexed, group, entry);
            if (data == NULL)
                return false;
        }
    index_entry = tdx_article_entry(data, artnum, entry->high);
    if (index_entry == NULL)
        return false;
    if (token != NULL)
        *token = index_entry->token;
    return true;
}
