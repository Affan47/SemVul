quota_link_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                int32_t op_ret, int32_t op_errno, inode_t *inode,
                struct iatt *buf, struct iatt *preparent,
                struct iatt *postparent)
{
        int32_t               ret          = -1;
        quota_local_t        *local        = NULL;
        quota_inode_ctx_t    *ctx          = NULL;
        quota_dentry_t       *dentry       = NULL;
        char                  found        = 0;

        if (op_ret < 0) {
                goto out;
        }

        local = (quota_local_t *) frame->local;

        quota_update_size (this, local->loc.parent, NULL, NULL,
                           (buf->ia_blocks * 512));

        ret = quota_inode_ctx_get (inode, -1, this, NULL, NULL, &ctx, 0);
        if ((ret == -1) || (ctx == NULL)) {
                gf_log (this->name, GF_LOG_WARNING, "cannot find quota "
                        "context in %s (gfid:%s)", local->loc.path,
                        uuid_utoa (inode->gfid));
                op_ret = -1;
                op_errno = EINVAL;
                goto out;
        }

        LOCK (&ctx->lock);
        {
                list_for_each_entry (dentry, &ctx->parents, next) {
                        if ((strcmp (dentry->name, local->loc.name) == 0) &&
                            (uuid_compare (local->loc.parent->gfid,
                                           dentry->par) == 0)) {
                                found = 1;
                                gf_log (this->name, GF_LOG_WARNING,
                                        "new entry being linked (name:%s) for "
                                        "inode (gfid:%s) is already present "
                                        "in inode-dentry-list", dentry->name,
                                        uuid_utoa (local->loc.inode->gfid));
                                break;
                        }
                }

                if (!found) {
                        dentry = __quota_dentry_new (ctx,
                                                     (char *)local->loc.name,
                                                     local->loc.parent->gfid);
                        if (dentry == NULL) {
                                gf_log (this->name, GF_LOG_WARNING,
                                        "cannot create a new dentry (name:%s) "
                                        "for inode(gfid:%s)", local->loc.name,
                                        uuid_utoa (local->loc.inode->gfid));
                                op_ret = -1;
                                op_errno = ENOMEM;
                                goto unlock;
                        }
                }

                ctx->buf = *buf;
        }
unlock:
        UNLOCK (&ctx->lock);

out:
        QUOTA_STACK_UNWIND (link, frame, op_ret, op_errno, inode, buf,
                            preparent, postparent);

        return 0;
}
