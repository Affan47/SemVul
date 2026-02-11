afr_create_wind_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno,
                     fd_t *fd, inode_t *inode, struct iatt *buf,
                     struct iatt *preparent, struct iatt *postparent)
{
        afr_local_t     *local = NULL;
        afr_private_t   *priv  = NULL;
        uint64_t        ctx = 0;
        afr_fd_ctx_t    *fd_ctx = NULL;
        int             ret = 0;
        int             call_count = -1;
        int             child_index = -1;
        int32_t         *fresh_children = NULL;

        local = frame->local;
        priv  = this->private;

        child_index = (long) cookie;

        LOCK (&frame->lock);
        {
                if (afr_fop_failed (op_ret, op_errno))
                        afr_transaction_fop_failed (frame, this, child_index);

                if (op_ret != -1) {
                        local->op_ret = op_ret;

                        ret = afr_fd_ctx_set (this, fd);

                        if (ret < 0) {
                                gf_log (this->name, GF_LOG_ERROR,
                                        "could not set ctx on fd=%p", fd);

                                local->op_ret   = -1;
                                local->op_errno = -ret;
                                goto unlock;
                        }

                        ret = fd_ctx_get (fd, this, &ctx);

                        if (ret < 0) {
                                gf_log (this->name, GF_LOG_ERROR,
                                        "could not get fd ctx for fd=%p", fd);
                                local->op_ret   = -1;
                                local->op_errno = -ret;
                                goto unlock;
                        }

                        fd_ctx = (afr_fd_ctx_t *)(long) ctx;

                        fd_ctx->opened_on[child_index] = AFR_FD_OPENED;
                        fd_ctx->flags                  = local->cont.create.flags;

                        if (local->success_count == 0)
                                local->cont.create.buf        = *buf;

                        if (child_index == local->read_child_index) {
                                local->cont.create.read_child_buf = *buf;
                                local->cont.create.preparent      = *preparent;
                                local->cont.create.postparent     = *postparent;
                        }

                        local->cont.create.inode = inode;

                        fresh_children = local->fresh_children;
                        fresh_children[local->success_count] = child_index;
                        local->success_count++;
                }

                local->op_errno = op_errno;
        }

unlock:
        UNLOCK (&frame->lock);

        call_count = afr_frame_return (frame);

        if (call_count == 0) {
                afr_set_read_ctx_from_policy (this, inode,
                                              local->fresh_children,
                                              local->read_child_index,
                                              priv->read_child);
                local->transaction.unwind (frame, this);

                local->transaction.resume (frame, this);
        }

        return 0;
}
