qr_ftruncate_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
                  struct iatt *postbuf, dict_t *xdata)
{
        int32_t           ret      = 0;
        uint64_t          value    = 0;
        qr_inode_t       *qr_inode = NULL;
        qr_local_t       *local    = NULL;
        qr_private_t     *priv     = NULL;
        qr_inode_table_t *table    = NULL;

        GF_ASSERT (frame);

        if (op_ret == -1) {
                goto out;
        }

        local = frame->local;
        if ((local == NULL) || (local->fd == NULL)
            || (local->fd->inode == NULL)) {
                op_ret = -1;
                op_errno = EINVAL;
                gf_log (frame->this->name, GF_LOG_WARNING, "cannot get inode");
                goto out;
        }

        if ((this == NULL) || (this->private == NULL)) {
                gf_log (frame->this->name, GF_LOG_WARNING,
                        (this == NULL) ? "xlator object (this) is NULL"
                        : "cannot get quick read configuration from xlator "
                        "object");
                op_ret = -1;
                op_errno = EINVAL;
                goto out;
        }

        priv = this->private;
        table = &priv->table;

        LOCK (&table->lock);
        {
                ret = inode_ctx_get (local->fd->inode, this, &value);
                if (ret == 0) {
                        qr_inode = (qr_inode_t *)(long) value;

                        if (qr_inode) {
                                if (qr_inode->stbuf.ia_size != postbuf->ia_size)
                                {
                                        inode_ctx_del (local->fd->inode, this,
                                                       NULL);
                                        __qr_inode_free (qr_inode);
                                }
                        }
                }
        }
        UNLOCK (&table->lock);

out:
        QR_STACK_UNWIND (ftruncate, frame, op_ret, op_errno, prebuf,
                         postbuf, xdata);
        return 0;
}
