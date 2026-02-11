event_pool_new_epoll (int count)
{
        struct event_pool *event_pool = NULL;
        int                epfd = -1;

        event_pool = GF_CALLOC (1, sizeof (*event_pool),
                                gf_common_mt_event_pool);

        if (!event_pool)
                goto out;

        event_pool->count = count;
        event_pool->reg = GF_CALLOC (event_pool->count,
                                     sizeof (*event_pool->reg),
                                     gf_common_mt_reg);

        if (!event_pool->reg) {
                GF_FREE (event_pool);
                event_pool = NULL;
                goto out;
        }

        epfd = epoll_create (count);

        if (epfd == -1) {
                gf_log ("epoll", GF_LOG_ERROR, "epoll fd creation failed (%s)",
                        strerror (errno));
                GF_FREE (event_pool->reg);
                GF_FREE (event_pool);
                event_pool = NULL;
                goto out;
        }

        event_pool->fd = epfd;

        event_pool->count = count;

        pthread_mutex_init (&event_pool->mutex, NULL);
        pthread_cond_init (&event_pool->cond, NULL);

out:
        return event_pool;
}
