dht_fsyncdir (call_frame_t *frame, xlator_t *this, fd_t *fd,
              int datasync, dict_t *xdata)
{
        dht_local_t  *local  = NULL;
        dht_conf_t   *conf = NULL;
        int           op_errno = -1;
        int           i = -1;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (fd, err);
        VALIDATE_OR_GOTO (this->private, err);

        conf = this->private;

        local = dht_local_init (frame, NULL, NULL, GF_FOP_FSYNCDIR);
        if (!local) {
                op_errno = ENOMEM;
                goto err;
        }

        local->fd = fd_ref (fd);
        local->call_cnt = conf->subvolume_cnt;

        for (i = 0; i < conf->subvolume_cnt; i++) {
                STACK_WIND (frame, dht_fsyncdir_cbk,
                            conf->subvolumes[i],
                            conf->subvolumes[i]->fops->fsyncdir,
                            fd, datasync, xdata);
        }

        return 0;

err:
        op_errno = (op_errno == -1) ? errno : op_errno;
        DHT_STACK_UNWIND (fsyncdir, frame, -1, op_errno, NULL);

        return 0;
}
