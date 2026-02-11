dht_readv2 (xlator_t *this, call_frame_t *frame, int op_ret)
{
        dht_local_t *local  = NULL;
        xlator_t    *subvol = NULL;
        int          op_errno = EINVAL;

        local = frame->local;
        if (!local)
                goto out;

        op_errno = local->op_errno;
        if (op_ret == -1)
                goto out;

        local->call_cnt = 2;
        subvol = local->cached_subvol;

        STACK_WIND (frame, dht_readv_cbk, subvol, subvol->fops->readv,
                    local->fd, local->rebalance.size, local->rebalance.offset);

        return 0;

out:
        DHT_STACK_UNWIND (readv, frame, -1, op_errno, NULL, 0, NULL, NULL);
        return 0;
}
