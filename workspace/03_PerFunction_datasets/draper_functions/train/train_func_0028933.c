dht_fsetxattr (call_frame_t *frame, xlator_t *this,
               fd_t *fd, dict_t *xattr, int flags, dict_t *xdata)
{
        xlator_t     *subvol   = NULL;
        dht_local_t  *local    = NULL;
        int           op_errno = EINVAL;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (fd, err);
        VALIDATE_OR_GOTO (fd->inode, err);

        GF_IF_INTERNAL_XATTR_GOTO ("trusted.glusterfs.dht*", xattr,
                                   op_errno, err);

        local = dht_local_init (frame, NULL, fd, GF_FOP_FSETXATTR);
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

        local->call_cnt = 1;

        STACK_WIND (frame, dht_err_cbk, subvol, subvol->fops->fsetxattr,
                    fd, xattr, flags, NULL);

        return 0;

err:
        op_errno = (op_errno == -1) ? errno : op_errno;
        DHT_STACK_UNWIND (fsetxattr, frame, -1, op_errno, NULL);

        return 0;
}
