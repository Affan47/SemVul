dht_truncate (call_frame_t *frame, xlator_t *this, loc_t *loc, off_t offset)
{
        xlator_t     *subvol = NULL;
        int           op_errno = -1;
        dht_local_t  *local = NULL;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (loc, err);
        VALIDATE_OR_GOTO (loc->inode, err);
        VALIDATE_OR_GOTO (loc->path, err);

        local = dht_local_init (frame, loc, NULL, GF_FOP_TRUNCATE);
        if (!local) {
                op_errno = ENOMEM;
                goto err;
        }

        local->rebalance.offset = offset;
        local->call_cnt = 1;
        subvol = local->cached_subvol;
        if (!subvol) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "no cached subvolume for path=%s", loc->path);
                op_errno = EINVAL;
                goto err;
        }

        STACK_WIND (frame, dht_truncate_cbk,
                    subvol, subvol->fops->truncate,
                    loc, offset);

        return 0;

err:
        op_errno = (op_errno == -1) ? errno : op_errno;
        DHT_STACK_UNWIND (truncate, frame, -1, op_errno, NULL, NULL);

        return 0;
}
