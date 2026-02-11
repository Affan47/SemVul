marker_fsetattr (call_frame_t *frame, xlator_t *this, fd_t *fd,
                 struct iatt *stbuf, int32_t valid)
{
        int32_t          ret   = 0;
        marker_local_t  *local = NULL;
        marker_conf_t   *priv  = NULL;

        priv = this->private;

        if (priv->feature_enabled == 0)
                goto wind;

        ALLOCATE_OR_GOTO (local, marker_local_t, err);

        MARKER_INIT_LOCAL (frame, local);

        ret = marker_inode_loc_fill (fd->inode, &local->loc);

        if (ret == -1)
                goto err;
wind:
        STACK_WIND (frame, marker_fsetattr_cbk, FIRST_CHILD (this),
                    FIRST_CHILD (this)->fops->fsetattr, fd, stbuf, valid);
        return 0;
err:
        STACK_UNWIND_STRICT (fsetattr, frame, -1, ENOMEM, NULL, NULL);

        return 0;
}
