dht_entrylk (call_frame_t *frame, xlator_t *this,
             const char *volume, loc_t *loc, const char *basename,
             entrylk_cmd cmd, entrylk_type type)
{
        xlator_t     *subvol = NULL;
        int           op_errno = -1;
        dht_local_t  *local = NULL;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (loc, err);
        VALIDATE_OR_GOTO (loc->inode, err);
        VALIDATE_OR_GOTO (loc->path, err);

        local = dht_local_init (frame, loc, NULL, GF_FOP_ENTRYLK);
        if (!local) {
                op_errno = ENOMEM;
                goto err;
        }

        subvol = local->cached_subvol;
        if (!subvol) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "no cached subvolume for path=%s", loc->path);
                op_errno = EINVAL;
                goto err;
        }

        local->call_cnt = 1;

        STACK_WIND (frame, dht_entrylk_cbk,
                    subvol, subvol->fops->entrylk,
                    volume, loc, basename, cmd, type);

        return 0;

err:
        op_errno = (op_errno == -1) ? errno : op_errno;
        DHT_STACK_UNWIND (entrylk, frame, -1, op_errno);

        return 0;
}
