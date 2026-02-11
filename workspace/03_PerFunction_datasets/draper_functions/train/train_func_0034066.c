dht_flush2 (xlator_t *this, call_frame_t *frame, int op_ret)
{
        dht_local_t  *local  = NULL;
        xlator_t     *subvol = NULL;
        uint64_t      tmp_subvol = 0;
        int           ret = -1;

        local = frame->local;

        ret = fd_ctx_get (local->fd, this, &tmp_subvol);
        if (!ret)
                subvol = (xlator_t *)(long)tmp_subvol;

        if (!subvol)
                subvol = local->cached_subvol;

        local->call_cnt = 2;

        STACK_WIND (frame, dht_flush_cbk,
                    subvol, subvol->fops->flush, local->fd, NULL);

        return 0;
}
