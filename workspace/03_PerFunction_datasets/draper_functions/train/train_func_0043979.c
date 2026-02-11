check_conflict(const CacheConfig *cache,
               int narrays,
               int array_size,
               int access_size)
{
    Range *head;
    Range *r;
    int i;
    int offset;

#define MAX_CONFLICT 10
    int conflict_size[MAX_CONFLICT];
    int total_conflict_size = 0;
    int no_conflict_size = 0;
    int no_access_size = 0;

    int cache_size = cache->size;
    int cache_assoc = cache->assoc;
    int cache_size0 = cache_size / cache_assoc;

    for (i = 0; i < MAX_CONFLICT; i++)
        conflict_size[i] = 0;

    head = range_new(0, cache_size0, 0);

    offset = 0;
    for (i = 0; i < narrays; i++) {
        int end = offset + access_size;
        int next_offset = (offset + array_size) % cache_size0;

        while (end > 0) {
            int end0 = (end < cache_size0 ? end : cache_size0);

#ifdef DEBUG_CHECK_CONFLICT
            fprintf(stdout, "[%d - %d]\n", offset, end0);
#endif
            range_list_add(head, offset, end0);

            offset = (end0 == cache_size0 ? 0 : end0);
            end -= cache_size0;
        }
        offset = next_offset;
    }

    for (r = head; r != NULL; r = r->next) {
        int size = r->end - r->begin;

        int index = r->n_arrays < MAX_CONFLICT ? r->n_arrays : MAX_CONFLICT - 1;
        conflict_size[index] += size;

        if (r->n_arrays == 0) {
            no_access_size += size;
        } else if (r->n_arrays > (cache_assoc / cache->procs)) {
            total_conflict_size += size;
        } else {
            no_conflict_size += size;
        }
    }

    if (verbose_level > 1) {
        fprintf(stdout,
                "conflict check: cache[size=%d, assoc=%d, procs=%d], data_size=%d, access_size=%d\n",
                cache->size,
                cache->assoc,
                cache->procs,
                array_size * narrays,
                access_size * narrays);

        if (verbose_level > 2) {
            for (r = head; r != NULL; r = r->next) {
                fprintf(stdout, "%10d - %10d (%10d): %d\n",
                        r->begin,
                        r->end,
                        r->end - r->begin,
                        r->n_arrays);
            }
        }

        for (i = 0; i < MAX_CONFLICT; i++) {
            fprintf(stdout, "conflict_size[%d%s] = %10d\n",
                    i,
                    i == MAX_CONFLICT - 1 ? "-" : "",
                    conflict_size[i]);
        }

        fprintf(stdout, "\ttotal_conflist_size = %d\n", total_conflict_size);
        fprintf(stdout, "\tno_conflict_size = %d\n", no_conflict_size);
        fprintf(stdout, "\tno_access_size = %d\n", no_access_size);
        fprintf(stdout, "\tconflict rate = %.2f%%\n",
                ((double)total_conflict_size)
                / (total_conflict_size + no_conflict_size) * 100);
    }

    if (total_conflict_size > 0)
        return TRUE;
    else
        return FALSE;
}
