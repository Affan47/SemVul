quota_stat_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                int32_t op_ret, int32_t op_errno, struct iatt *buf, dict_t *xdata)
{
        quota_local_t     *local = NULL;
        quota_inode_ctx_t *ctx   = NULL;

        if (op_ret < 0) {
                goto out;
        }

        local = frame->local;
        if (local == NULL) {
                gf_log (this->name, GF_LOG_WARNING, "local is NULL");
                goto out;
        }

        quota_inode_ctx_get (local->loc.inode, -1, this, NULL, NULL,
                             &ctx, 0);
        if (ctx == NULL) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "quota context not set in inode (gfid:%s)",
                        uuid_utoa (local->loc.inode->gfid));
                goto out;
        }

        LOCK (&ctx->lock);
        {
                if (buf)
                        ctx->buf = *buf;
        }
        UNLOCK (&ctx->lock);

out:
        QUOTA_STACK_UNWIND (stat, frame, op_ret, op_errno, buf, xdata);
        return 0;
}
