fuse_dumper (xlator_t *this, fuse_in_header_t *finh, void *msg)
{
        fuse_private_t *priv = NULL;
        struct iovec diov[3];
        char r = 'R';
        int ret = 0;

        priv = this->private;

        diov[0].iov_base = &r;
        diov[0].iov_len  = 1;
        diov[1].iov_base = finh;
        diov[1].iov_len  = sizeof (*finh);
        diov[2].iov_base = msg;
        diov[2].iov_len  = finh->len - sizeof (*finh);

        pthread_mutex_lock (&priv->fuse_dump_mutex);
        ret = writev (priv->fuse_dump_fd, diov, 3);
        pthread_mutex_unlock (&priv->fuse_dump_mutex);
        if (ret == -1)
                gf_log ("glusterfs-fuse", GF_LOG_ERROR,
                        "failed to dump fuse message (R): %s",
                        strerror (errno));

        priv->fuse_ops0[finh->opcode] (this, finh, msg);
}
