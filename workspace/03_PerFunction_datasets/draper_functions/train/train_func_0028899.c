dht_rmdir (call_frame_t *frame, xlator_t *this, loc_t *loc, int flags,
           dict_t *xdata)
{
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

        local = dht_local_init (frame, loc, NULL, GF_FOP_RMDIR);
        if (!local) {
                op_errno = ENOMEM;
                goto err;
        }

        local->call_cnt = conf->subvolume_cnt;
        local->op_ret   = 0;
        local->fop_succeeded = 0;

        local->flags = flags;

        local->fd = fd_create (local->loc.inode, frame->root->pid);
        if (!local->fd) {

                op_errno = ENOMEM;
                goto err;
        }

        for (i = 0; i < conf->subvolume_cnt; i++) {
                STACK_WIND (frame, dht_rmdir_opendir_cbk,
                            conf->subvolumes[i],
                            conf->subvolumes[i]->fops->opendir,
                            loc, local->fd, NULL);
        }

        return 0;

err:
        op_errno = (op_errno == -1) ? errno : op_errno;
        DHT_STACK_UNWIND (rmdir, frame, -1, op_errno,
                          NULL, NULL, NULL);

        return 0;
}
