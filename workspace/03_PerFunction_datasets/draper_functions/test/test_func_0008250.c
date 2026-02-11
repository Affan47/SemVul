entry_audit(struct group_data *data, struct index_entry *entry,
            const char *group, ARTNUM article, bool fix)
{
    struct index_entry new_entry;
    off_t offset;

    if (entry->length < 0) {
        warn("tradindexed: negative length %d in %s:%lu", entry->length,
             group, article);
        if (fix)
            goto clear;
        return;
    }
    if (entry->offset > data->datalen || entry->length > data->datalen) {
        warn("tradindexed: offset %lu or length %lu out of bounds for %s:%lu",
             (unsigned long) entry->offset, (unsigned long) entry->length,
             group, article);
        if (fix)
            goto clear;
        return;
    }
    if (entry->offset + entry->length > data->datalen) {
        warn("tradindexed: offset %lu plus length %lu out of bounds for"
             " %s:%lu", (unsigned long) entry->offset,
             (unsigned long) entry->length, group, article);
        if (fix)
            goto clear;
        return;
    }
    if (!overview_check(data->data + entry->offset, entry->length, article)) {
        warn("tradindexed: malformed overview data for %s:%lu", group,
             article);
        if (fix)
            goto clear;
    }
    return;

 clear:
    new_entry = *entry;
    new_entry.offset = 0;
    new_entry.length = 0;
    offset = (entry - data->index) * sizeof(struct index_entry);
    if (xpwrite(data->indexfd, &new_entry, sizeof(new_entry), offset) != 0)
        warn("tradindexed: unable to repair %s:%lu", group, article);
}
