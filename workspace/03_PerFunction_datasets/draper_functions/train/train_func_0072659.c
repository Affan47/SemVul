gf_timer_registry_init (glusterfs_ctx_t *ctx)
{
        if (ctx == NULL) {
                gf_log_callingfn ("timer", GF_LOG_ERROR, "invalid argument");
                return NULL;
        }

        if (!ctx->timer) {
                gf_timer_registry_t *reg = NULL;

                reg = GF_CALLOC (1, sizeof (*reg),
                                 gf_common_mt_gf_timer_registry_t);
                if (!reg)
                        goto out;

                pthread_mutex_init (&reg->lock, NULL);
                reg->active.next = &reg->active;
                reg->active.prev = &reg->active;
                reg->stale.next = &reg->stale;
                reg->stale.prev = &reg->stale;

                ctx->timer = reg;
                pthread_create (&reg->th, NULL, gf_timer_proc, ctx);
        }
out:
        return ctx->timer;
}
