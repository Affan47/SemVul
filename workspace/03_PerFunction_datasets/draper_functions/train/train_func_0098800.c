__iobuf_pool_add_arena (struct iobuf_pool *iobuf_pool, size_t page_size,
                        int32_t num_pages)
{
        struct iobuf_arena *iobuf_arena  = NULL;
        int                 index        = 0;

        index = gf_iobuf_get_arena_index (page_size);
        if (index == -1) {
                gf_log ("iobuf", GF_LOG_ERROR, "page_size (%zu) of "
                        "iobufs in arena being added is greater than max "
                        "available", page_size);
                return NULL;
        }

        iobuf_arena = __iobuf_arena_unprune (iobuf_pool, page_size);

        if (!iobuf_arena)
                iobuf_arena = __iobuf_arena_alloc (iobuf_pool, page_size,
                                                   num_pages);

        if (!iobuf_arena) {
                gf_log (THIS->name, GF_LOG_WARNING, "arena not found");
                return NULL;
        }

        list_add_tail (&iobuf_arena->list, &iobuf_pool->arenas[index]);

        return iobuf_arena;
}
