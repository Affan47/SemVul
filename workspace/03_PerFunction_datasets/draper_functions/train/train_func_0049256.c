dht_readv (call_frame_t *frame, xlator_t *this,
           fd_t *fd, size_t size, off_t off)
{
        xlator_t     *subvol = NULL;
        int           op_errno = -1;
        dht_local_t  *local = NULL;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (fd, err);

        local = dht_local_init (frame, NULL, fd, GF_FOP_READ);
        if (!local) {
                op_errno = ENOMEM;
                goto err;
        }

        subvol = local->cached_subvol;
        if (!subvol) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "no cached subvolume for fd=%p", fd);
                op_errno = EINVAL;
                goto err;
        }

        local->rebalance.offset = off;
        local->rebalance.size   = size;
        local->call_cnt = 1;

        STACK_WIND (frame, dht_readv_cbk,
                    subvol, subvol->fops->readv,
                    fd, size, off);

        return 0;

err:
        op_errno = (op_errno == -1) ? errno : op_errno;
        DHT_STACK_UNWIND (readv, frame, -1, op_errno, NULL, 0, NULL, NULL);

        return 0;
}
