index_audit_deleted(struct group_entry *entry, long number, bool fix)
{
    if (entry->deleted != 0 && !HashEmpty(entry->hash)) {
        warn("tradindexed: entry %ld has a delete time but a non-zero hash",
             number);
        if (fix) {
            HashClear(&entry->hash);
            inn_msync_page(entry, sizeof(*entry), MS_ASYNC);
        }
    }
}
