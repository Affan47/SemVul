fuse_migrate_fd_error (xlator_t *this, fd_t *fd)
{
        fuse_fd_ctx_t *fdctx = NULL;
        char           error = 0;

        fdctx = fuse_fd_ctx_get (this, fd);
        if (fdctx != NULL) {
                if (fdctx->migration_failed) {
                        error = 1;
                }
        }

        return error;
}
