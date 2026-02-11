fs_query_cache_flush(fs_query_state *qs, int verbosity)
{

    if (!qs->bind_cache) return 1;

    g_static_mutex_lock(&qs->cache_mutex);

    for (int i=0; i<CACHE_SIZE; i++) {
        if (qs->bind_cache[i].filled) {
            if (verbosity > 0) {
                printf("# cache entry %d\n", i);
                printf("#   hits=%d, all=%s, flags=%08x, offset=%d, limit=%d\n", qs->bind_cache[i].hits, qs->bind_cache[i].all ? "true" : "false", qs->bind_cache[i].flags, qs->bind_cache[i].offset, qs->bind_cache[i].limit);
                printf("#   bind(%016llx, %016llx, %016llx, %016llx)\n", qs->bind_cache[i].key[0], qs->bind_cache[i].key[1], qs->bind_cache[i].key[2], qs->bind_cache[i].key[3]);
            }
            qs->bind_cache[i].filled = 0;
            qs->bind_cache[i].all = 0;
            qs->bind_cache[i].flags = 0;
            qs->bind_cache[i].offset = 0;
            qs->bind_cache[i].limit = 0;
            for (int s=0; s<4; s++) {
                qs->bind_cache[i].key[s] = 0;
                fs_rid_vector_free(qs->bind_cache[i].res[s]);
                qs->bind_cache[i].res[s] = 0;
            }
        }
    }
    if (verbosity > 0) {
        printf("# @resolver@ cache_stats hits %u l1 %u l2 %u fails %u (%.4f perc. success)\n",
            qs->cache_hits,qs->cache_success_l1,qs->cache_success_l2,qs->cache_fail,
            ((((double)qs->cache_success_l1)+((double)qs->cache_success_l2))/((double)qs->cache_hits))*100.0);
        printf("# @resolver@ cache_stats items pre cached %u calls %u elapse %.3f\n",
        qs->pre_cache_total,qs->resolve_all_calls,qs->resolve_all_elapse);
        printf("# @resolver@ cache_stats resolve single calls %u elapse %.3f\n",
        qs->cache_fail,qs->resolve_unique_elapse);
    }

    g_static_mutex_unlock(&qs->cache_mutex);

    return 0;
}
