ExpandMonitorCache(PRUintn new_size_log2)
{
    MonitorCacheEntry **old_hash_buckets, *p;
    PRUintn i, entries, old_num_hash_buckets, added;
    MonitorCacheEntry **new_hash_buckets;
    MonitorCacheEntryBlock *new_block;

    entries = 1L << new_size_log2;


    new_block = (MonitorCacheEntryBlock*)
        PR_CALLOC(sizeof(MonitorCacheEntryBlock)
        + (entries - 1) * sizeof(MonitorCacheEntry));
    if (NULL == new_block) return PR_FAILURE;


    for (i = 0, p = new_block->entries; i < entries; i++, p++) {
        p->mon = PR_NewMonitor();
        if (!p->mon)
            break;
    }
    added = i;
    if (added != entries) {
        MonitorCacheEntryBlock *realloc_block;

        if (added == 0) {

            PR_DELETE(new_block);
            return PR_FAILURE;
        }


        realloc_block = (MonitorCacheEntryBlock*)
            PR_REALLOC(new_block, sizeof(MonitorCacheEntryBlock)
            + (added - 1) * sizeof(MonitorCacheEntry));
        if (realloc_block)
            new_block = realloc_block;
    }


    for (i = 0, p = new_block->entries; i < added - 1; i++, p++)
        p->next = p + 1;
    p->next = free_entries;
    free_entries = new_block->entries;
    num_free_entries += added;
    new_block->next = mcache_blocks;
    mcache_blocks = new_block;


    new_hash_buckets = (MonitorCacheEntry**)
        PR_CALLOC(entries * sizeof(MonitorCacheEntry*));
    if (NULL == new_hash_buckets) {


        PR_LOG(_pr_cmon_lm, PR_LOG_WARNING,
               ("unable to grow monitor cache hash buckets"));
        return PR_SUCCESS;
    }


    hash_mask = entries - 1;


    old_hash_buckets = hash_buckets;
    old_num_hash_buckets = num_hash_buckets;
    for (i = 0; i < old_num_hash_buckets; i++) {
        p = old_hash_buckets[i];
        while (p) {
            MonitorCacheEntry *next = p->next;


            PRUintn hash = HASH(p->address);
            p->next = new_hash_buckets[hash];
            new_hash_buckets[hash] = p;

            p = next;
        }
    }


    hash_buckets = new_hash_buckets;
    num_hash_buckets = entries;
    num_hash_buckets_log2 = new_size_log2;
    PR_DELETE(old_hash_buckets);

    PR_LOG(_pr_cmon_lm, PR_LOG_NOTICE,
           ("expanded monitor cache to %d (buckets %d)",
            num_free_entries, entries));

    return PR_SUCCESS;
}
