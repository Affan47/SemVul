dht_open2 (xlator_t *this, call_frame_t *frame, int op_ret)
{
        dht_local_t *local  = NULL;
        xlator_t    *subvol = NULL;
        int          op_errno = EINVAL;

        local = frame->local;
        if (!local)
                goto out;

        op_errno = ENOENT;
        if (op_ret)
                goto out;

        local->call_cnt = 2;
        subvol = local->cached_subvol;

        STACK_WIND (frame, dht_open_cbk, subvol, subvol->fops->open,
                    &local->loc, local->rebalance.flags, local->fd,
                    local->rebalance.wbflags);
        return 0;

out:
        DHT_STACK_UNWIND (stat, frame, -1, op_errno, NULL);
        return 0;
}
