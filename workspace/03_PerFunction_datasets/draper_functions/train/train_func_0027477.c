dht_statfs (call_frame_t *frame, xlator_t *this, loc_t *loc)
{
        xlator_t     *subvol = NULL;
        dht_local_t  *local  = NULL;
        dht_conf_t   *conf = NULL;
        int           op_errno = -1;
        int           i = -1;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (loc, err);
        VALIDATE_OR_GOTO (loc->inode, err);
        VALIDATE_OR_GOTO (loc->path, err);
        VALIDATE_OR_GOTO (this->private, err);

        conf = this->private;

        local = dht_local_init (frame, NULL, NULL, GF_FOP_STATFS);
        if (!local) {
                op_errno = ENOMEM;
                goto err;
        }

        if (IA_ISDIR (loc->inode->ia_type)) {
                local->call_cnt = conf->subvolume_cnt;

                for (i = 0; i < conf->subvolume_cnt; i++) {
                        STACK_WIND (frame, dht_statfs_cbk,
                                    conf->subvolumes[i],
                                    conf->subvolumes[i]->fops->statfs, loc);
                }
                return 0;
        }

        subvol = dht_subvol_get_cached (this, loc->inode);
        if (!subvol) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "no cached subvolume for path=%s", loc->path);
                op_errno = EINVAL;
                goto err;
        }

        local->call_cnt = 1;

        STACK_WIND (frame, dht_statfs_cbk,
                    subvol, subvol->fops->statfs, loc);

        return 0;

err:
        op_errno = (op_errno == -1) ? errno : op_errno;
        DHT_STACK_UNWIND (statfs, frame, -1, op_errno, NULL);

        return 0;
}
