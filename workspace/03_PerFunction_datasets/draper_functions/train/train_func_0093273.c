fuse_handle_opened_fds (xlator_t *this, xlator_t *old_subvol,
                        xlator_t *new_subvol)
{
        fuse_private_t *priv      = NULL;
        fdentry_t      *fdentries = NULL;
        uint32_t        count     = 0;
        fdtable_t      *fdtable   = NULL;
        int             i         = 0;
        fd_t           *fd        = NULL;
        int32_t         ret       = 0;
        fuse_fd_ctx_t  *fdctx     = NULL;

        priv = this->private;

        fdtable = priv->fdtable;

        fdentries = gf_fd_fdtable_copy_all_fds (fdtable, &count);
        if (fdentries != NULL) {
                for (i = 0; i < count; i++) {
                        fd = fdentries[i].fd;
                        if (fd == NULL)
                                continue;

                        ret = fuse_migrate_fd (this, fd, old_subvol,
                                                       new_subvol);
                        if (ret < 0) {
                                if (ret == -1) {
                                        fdctx = fuse_fd_ctx_check_n_create (fd,
                                                                         this);
                                        if (fdctx != NULL) {
                                                fdctx->migration_failed = 1;
                                                gf_log_callingfn ("glusterfs-"
                                                                  "fuse",
                                                                  GF_LOG_ERROR,
                                                                  "fd migration"
                                                                  " for the fd "
                                                                  "(%p), with"
                                                                  "context (%p)"
                                                                  " failed", fd,
                                                                  fdctx);
                                        }
                                } else {


                                }
                        } else {
                                fdctx = fuse_fd_ctx_get (this, fd);
                                if (fdctx != NULL) {
                                        fdctx->migration_failed = 0;
                                }
                        }
                }

                for (i = 0; i < count ; i++) {
                        fd = fdentries[i].fd;
                        if (fd)
                                fd_unref (fd);
                }
                GF_FREE (fdentries);
        }

        return 0;
}
