fd_lk_ctx_try_ref (fd_lk_ctx_t *lk_ctx)
{
        int         ret         = -1;
        fd_lk_ctx_t *new_lk_ctx = NULL;

        if (!lk_ctx) {
                goto out;
        }

        ret = TRY_LOCK (&lk_ctx->lock);
        if (ret)
                goto out;

        new_lk_ctx = _fd_lk_ctx_ref (lk_ctx);
        UNLOCK (&lk_ctx->lock);

out:
        return new_lk_ctx;
}
