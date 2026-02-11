tdx_data_index_dump(struct group_data *data, FILE *output)
{
    ARTNUM current;
    struct index_entry *entry, *end;

    if (data->index == NULL)
        if (!map_index(data))
            return;

    current = data->base;
    end = data->index + (data->indexlen / sizeof(struct index_entry));
    for (entry = data->index; entry < end; entry++) {
        fprintf(output, "%lu %lu %lu %lu %lu %s\n", current,
                (unsigned long) entry->offset, (unsigned long) entry->length,
                (unsigned long) entry->arrived,
                (unsigned long) entry->expires, TokenToText(entry->token));
        current++;
    }
}
