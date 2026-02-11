afr_readv (call_frame_t *frame, xlator_t *this,
           fd_t *fd, size_t size, off_t offset, uint32_t flags, dict_t *xdata)
{
        afr_private_t * priv       = NULL;
        afr_local_t   * local      = NULL;
        xlator_t **     children   = NULL;
        int             call_child = 0;
        int32_t         op_errno   = 0;
        int32_t         read_child = -1;
        int             ret        = -1;

        VALIDATE_OR_GOTO (frame, out);
        VALIDATE_OR_GOTO (this, out);
        VALIDATE_OR_GOTO (this->private, out);
        VALIDATE_OR_GOTO (fd, out);

        priv     = this->private;
        children = priv->children;

        if (afr_is_split_brain (this, fd->inode)) {
                op_errno = EIO;
                goto out;
        }

        AFR_LOCAL_ALLOC_OR_GOTO (frame->local, out);
        local = frame->local;

        ret = afr_local_init (local, priv, &op_errno);
        if (ret < 0)
                goto out;

        local->fresh_children = afr_children_create (priv->child_count);
        if (!local->fresh_children) {
                op_errno = ENOMEM;
                goto out;
        }

        read_child = afr_inode_get_read_ctx (this, fd->inode, local->fresh_children);
        ret = afr_get_call_child (this, local->child_up, read_child,
                                     local->fresh_children,
                                     &call_child,
                                     &local->cont.readv.last_index);
        if (ret < 0) {
                op_errno = -ret;
                goto out;
        }

        local->fd                    = fd_ref (fd);

        local->cont.readv.size       = size;
        local->cont.readv.offset     = offset;
        local->cont.readv.flags      = flags;

        afr_open_fd_fix (fd, this);

        STACK_WIND_COOKIE (frame, afr_readv_cbk,
                           (void *) (long) call_child,
                           children[call_child],
                           children[call_child]->fops->readv,
                           fd, size, offset, flags, xdata);

        ret = 0;
out:
        if (ret < 0) {
                AFR_STACK_UNWIND (readv, frame, -1, op_errno, NULL, 0, NULL,
                                  NULL, NULL);
        }
        return 0;
}
