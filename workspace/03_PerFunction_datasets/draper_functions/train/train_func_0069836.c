quota_symlink_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, inode_t *inode,
                   struct iatt *buf, struct iatt *preparent,
                   struct iatt *postparent, dict_t *xdata)
{
        int64_t            size   = 0;
        quota_local_t     *local  = NULL;
        quota_inode_ctx_t *ctx    = NULL;
        quota_dentry_t    *dentry = NULL;

        if (op_ret < 0) {
                goto out;
        }

        local = frame->local;
        size = buf->ia_blocks * 512;

        quota_update_size (this, local->loc.parent, NULL, NULL, size);

        quota_inode_ctx_get (local->loc.inode, -1, this, NULL, NULL,
                             &ctx, 1);
        if (ctx == NULL) {
                gf_log (this->name, GF_LOG_WARNING,
                        "quota context not set in inode (gfid:%s)",
                        uuid_utoa (local->loc.inode->gfid));
                goto out;
        }

        LOCK (&ctx->lock);
        {
                ctx->buf = *buf;

                dentry = __quota_dentry_new (ctx, (char *)local->loc.name,
                                             local->loc.parent->gfid);
                if (dentry == NULL) {
                        gf_log (this->name, GF_LOG_WARNING,
                                "cannot create a new dentry (name:%s) for "
                                "inode(gfid:%s)", local->loc.name,
                                uuid_utoa (local->loc.inode->gfid));
                        op_ret = -1;
                        op_errno = ENOMEM;
                }
        }
        UNLOCK (&ctx->lock);

out:
        QUOTA_STACK_UNWIND (symlink, frame, op_ret, op_errno, inode, buf,
                            preparent, postparent, xdata);

        return 0;
}
