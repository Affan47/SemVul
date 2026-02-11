marker_fsetxattr (call_frame_t *frame, xlator_t *this, fd_t *fd, dict_t *dict,
                  int32_t flags, dict_t *xdata)
{
        int32_t          ret   = 0;
        marker_local_t  *local = NULL;
        marker_conf_t   *priv  = NULL;

        priv = this->private;

        if (priv->feature_enabled == 0)
                goto wind;

        ret = call_from_sp_client_to_reset_tmfile (frame, this, dict);
        if (ret == 0)
                return 0;

        local = mem_get0 (this->local_pool);

        MARKER_INIT_LOCAL (frame, local);

        ret = marker_inode_loc_fill (fd->inode, &local->loc);

        if (ret == -1)
                goto err;
wind:
        STACK_WIND (frame, marker_fsetxattr_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->fsetxattr, fd, dict, flags, xdata);
        return 0;
err:
        STACK_UNWIND_STRICT (fsetxattr, frame, -1, ENOMEM, NULL);

        return 0;
}
