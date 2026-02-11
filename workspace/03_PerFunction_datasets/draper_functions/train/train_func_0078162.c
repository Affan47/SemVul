data_cache_reopen(struct tradindexed *global, const char *group,
                  struct group_entry *entry)
{
    struct group_data *data;

    tdx_cache_delete(global->cache, entry->hash);
    data = tdx_data_open(global->index, group, entry);
    if (data == NULL)
        return NULL;
    tdx_cache_insert(global->cache, entry->hash, data);
    return data;
}
