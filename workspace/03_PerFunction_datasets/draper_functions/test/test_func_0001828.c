quota_writev_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
                  struct iatt *postbuf, dict_t *xdata)
{
        int32_t                  ret            = 0;
        uint64_t                 ctx_int        = 0;
        quota_inode_ctx_t       *ctx            = NULL;
        quota_local_t           *local          = NULL;
        quota_dentry_t          *dentry         = NULL;
        int64_t                  delta          = 0;

        local = frame->local;

        if ((op_ret < 0) || (local == NULL)) {
                goto out;
        }

        ret = inode_ctx_get (local->loc.inode, this, &ctx_int);
        if (ret) {
                gf_log (this->name, GF_LOG_WARNING,
                        "%s: failed to get the context", local->loc.path);
                goto out;
        }

        ctx = (quota_inode_ctx_t *)(unsigned long) ctx_int;

        if (ctx == NULL) {
                gf_log (this->name, GF_LOG_WARNING,
                        "quota context not set in %s (gfid:%s)",
                        local->loc.path, uuid_utoa (local->loc.inode->gfid));
                goto out;
        }

        LOCK (&ctx->lock);
        {
                ctx->buf = *postbuf;
        }
        UNLOCK (&ctx->lock);

        list_for_each_entry (dentry, &ctx->parents, next) {
                delta = (postbuf->ia_blocks - prebuf->ia_blocks) * 512;
                quota_update_size (this, local->loc.inode,
                                   dentry->name, dentry->par, delta);
        }

out:
        QUOTA_STACK_UNWIND (writev, frame, op_ret, op_errno, prebuf, postbuf,
                            xdata);

        return 0;
}
