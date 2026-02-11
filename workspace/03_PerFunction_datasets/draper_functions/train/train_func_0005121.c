tdx_article_entry(struct group_data *data, ARTNUM article, ARTNUM high)
{
    struct index_entry *entry;
    ARTNUM offset;

    if (article > data->high && high > data->high) {
        unmap_index(data);
        map_index(data);
        data->high = high;

        data->remapoutoforder = true;
    } else if (innconf->nfsreader && stale_index(data))
        unmap_index(data);
    if (data->index == NULL)
        if (!map_index(data))
            return NULL;

    if (article < data->base)
        return NULL;
    offset = article - data->base;
    if (offset >= data->indexlen / sizeof(struct index_entry))
        return NULL;
    entry = data->index + offset;
    if (entry->length == 0)
        return NULL;
    return entry;
}
