nufa_create_linkfile_create_cbk (call_frame_t *frame, void *cookie,
                                 xlator_t *this, int op_ret, int op_errno,
                                 inode_t *inode, struct iatt *stbuf,
                                 struct iatt *preparent,
                                 struct iatt *postparent, dict_t *xdata)
{
        dht_local_t  *local = NULL;

        local = frame->local;

        if (op_ret == -1)
                goto err;

        STACK_WIND (frame, dht_create_cbk,
                    local->cached_subvol, local->cached_subvol->fops->create,
                    &local->loc, local->flags, local->mode, local->umask,
                    local->fd, local->params);

        return 0;

err:
        DHT_STACK_UNWIND (create, frame, -1, op_errno,
                          NULL, NULL, NULL, NULL, NULL, NULL);
        return 0;
}
