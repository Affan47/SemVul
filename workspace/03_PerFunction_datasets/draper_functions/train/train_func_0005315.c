fuse_init (xlator_t *this, fuse_in_header_t *finh, void *msg)
{
        struct fuse_init_in  *fini      = msg;
        struct fuse_init_out  fino      = {0,};
        fuse_private_t       *priv      = NULL;
        int                   ret       = 0;
        int                   pfd[2]    = {0,};
        pthread_t             messenger;

        priv = this->private;

        if (priv->init_recvd) {
                gf_log ("glusterfs-fuse", GF_LOG_ERROR,
                        "got INIT after first message");

                close (priv->fd);
                goto out;
        }

        priv->init_recvd = 1;

        if (fini->major != FUSE_KERNEL_VERSION) {
                gf_log ("glusterfs-fuse", GF_LOG_ERROR,
                        "unsupported FUSE protocol version %d.%d",
                        fini->major, fini->minor);

                close (priv->fd);
                goto out;
        }
        priv->proto_minor = fini->minor;

        fino.major = FUSE_KERNEL_VERSION;
        fino.minor = FUSE_KERNEL_MINOR_VERSION;
        fino.max_readahead = 1 << 17;
        fino.max_write = 1 << 17;
        fino.flags = FUSE_ASYNC_READ | FUSE_POSIX_LOCKS;
#if FUSE_KERNEL_MINOR_VERSION >= 12
        if (fini->minor >= 12) {


            fino.flags |= FUSE_DONT_MASK;
        }
#endif
#if FUSE_KERNEL_MINOR_VERSION >= 9
        if (fini->minor >= 6  &&
            fini->flags & FUSE_BIG_WRITES) {

                if (priv->direct_io_mode == 2)
                        priv->direct_io_mode = 0;
                fino.flags |= FUSE_BIG_WRITES;
        }


        if (fini->minor >= 12) {
                if (pipe(pfd) == -1) {
                        gf_log ("glusterfs-fuse", GF_LOG_ERROR,
                                "cannot create pipe pair (%s)",
                                strerror(errno));

                        close (priv->fd);
                        goto out;
                }
                priv->revchan_in  = pfd[0];
                priv->revchan_out = pfd[1];
                ret = pthread_create (&messenger, NULL, notify_kernel_loop,
                                      this);
                if (ret != 0) {
                        gf_log ("glusterfs-fuse", GF_LOG_ERROR,
                                "failed to start messenger daemon (%s)",
                                strerror(errno));

                        close (priv->fd);
                        goto out;
                }
                priv->reverse_fuse_thread_started = _gf_true;
        }
        if (fini->minor >= 13) {

                fino.max_background = 64;
                fino.congestion_threshold = 48;
        }
        if (fini->minor < 9)
                *priv->msg0_len_p = sizeof(*finh) + FUSE_COMPAT_WRITE_IN_SIZE;
#endif
        ret = send_fuse_obj (this, finh, &fino);
        if (ret == 0)
                gf_log ("glusterfs-fuse", GF_LOG_INFO,
                        "FUSE inited with protocol versions:"
                        " glusterfs %d.%d kernel %d.%d",
                        FUSE_KERNEL_VERSION, FUSE_KERNEL_MINOR_VERSION,
                        fini->major, fini->minor);
        else {
                gf_log ("glusterfs-fuse", GF_LOG_ERROR,
                        "FUSE init failed (%s)", strerror (ret));

                close (priv->fd);
        }

 out:
        GF_FREE (finh);
}
