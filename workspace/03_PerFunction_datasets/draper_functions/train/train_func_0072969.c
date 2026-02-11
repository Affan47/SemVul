gf_proc_dump_mempool_info (glusterfs_ctx_t *ctx)
{
        struct mem_pool *pool = NULL;

        gf_proc_dump_add_section ("mempool");

        list_for_each_entry (pool, &ctx->mempool_list, global_list) {
                gf_proc_dump_write ("-----", "-----");
                gf_proc_dump_write ("pool-name", "%s", pool->name);
                gf_proc_dump_write ("hot-count", "%d", pool->hot_count);
                gf_proc_dump_write ("cold-count", "%d", pool->cold_count);
                gf_proc_dump_write ("padded_sizeof", "%lu",
                                    pool->padded_sizeof_type);
                gf_proc_dump_write ("alloc-count", "%"PRIu64, pool->alloc_count);
                gf_proc_dump_write ("max-alloc", "%d", pool->max_alloc);
        }
}
