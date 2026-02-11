afr_opendir (call_frame_t *frame, xlator_t *this,
             loc_t *loc, fd_t *fd)
{
        afr_private_t * priv        = NULL;
        afr_local_t   * local       = NULL;
        int             child_count = 0;
        int             i           = 0;
        int             ret         = -1;
        int             call_count  = -1;
        int32_t         op_errno    = 0;

        VALIDATE_OR_GOTO (frame, out);
        VALIDATE_OR_GOTO (this, out);
        VALIDATE_OR_GOTO (this->private, out);

        priv = this->private;

        child_count = priv->child_count;

        ALLOC_OR_GOTO (frame->local, afr_local_t, out);
        local = frame->local;

        ret = afr_local_init (local, priv, &op_errno);
        if (ret < 0)
                goto out;

        loc_copy (&local->loc, loc);

        local->fd    = fd_ref (fd);

        call_count = local->call_count;

        for (i = 0; i < child_count; i++) {
                if (local->child_up[i]) {
                        STACK_WIND_COOKIE (frame, afr_opendir_cbk,
                                           (void*) (long) i,
                                           priv->children[i],
                                           priv->children[i]->fops->opendir,
                                           loc, fd);

                        if (!--call_count)
                                break;
                }
        }

        ret = 0;
out:
        if (ret < 0)
                AFR_STACK_UNWIND (opendir, frame, -1, op_errno, fd);

        return 0;
}
