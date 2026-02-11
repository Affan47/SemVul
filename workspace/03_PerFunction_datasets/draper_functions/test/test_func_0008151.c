iobuf_pool_prune (struct iobuf_pool *iobuf_pool)
{
        struct iobuf_arena *iobuf_arena = NULL;
        struct iobuf_arena *tmp         = NULL;
        int                 i           = 0;

        GF_VALIDATE_OR_GOTO ("iobuf", iobuf_pool, out);

        pthread_mutex_lock (&iobuf_pool->mutex);
        {
                for (i = 0; i < IOBUF_ARENA_MAX_INDEX; i++) {
                        if (list_empty (&iobuf_pool->arenas[i])) {
                                continue;
                        }

                        list_for_each_entry_safe (iobuf_arena, tmp,
                                                  &iobuf_pool->purge[i], list) {
                                __iobuf_arena_prune (iobuf_pool, iobuf_arena, i);
                        }
                }
        }
        pthread_mutex_unlock (&iobuf_pool->mutex);

out:
        return;
}
