posix_opendir (call_frame_t *frame, xlator_t *this,
               loc_t *loc, fd_t *fd)
{
        char *            real_path = NULL;
        int32_t           op_ret    = -1;
        int32_t           op_errno  = EINVAL;
        DIR *             dir       = NULL;
        struct posix_fd * pfd       = NULL;

        DECLARE_OLD_FS_ID_VAR;

        VALIDATE_OR_GOTO (frame, out);
        VALIDATE_OR_GOTO (this, out);
        VALIDATE_OR_GOTO (loc, out);
        VALIDATE_OR_GOTO (loc->path, out);
        VALIDATE_OR_GOTO (fd, out);

        SET_FS_ID (frame->root->uid, frame->root->gid);
        MAKE_REAL_PATH (real_path, this, loc->path);

        dir = opendir (real_path);

        if (dir == NULL) {
                op_errno = errno;
                gf_log (this->name, GF_LOG_ERROR,
                        "opendir failed on %s: %s",
                        loc->path, strerror (op_errno));
                goto out;
        }

        op_ret = dirfd (dir);
        if (op_ret < 0) {
                op_errno = errno;
                gf_log (this->name, GF_LOG_ERROR,
                        "dirfd() failed on %s: %s",
                        loc->path, strerror (op_errno));
                goto out;
        }

        pfd = GF_CALLOC (1, sizeof (*pfd), gf_posix_mt_posix_fd);
        if (!pfd) {
                op_errno = errno;
                goto out;
        }

        pfd->dir = dir;
        pfd->fd = dirfd (dir);
        pfd->path = gf_strdup (real_path);
        if (!pfd->path) {
                goto out;
        }

        op_ret = fd_ctx_set (fd, this, (uint64_t)(long)pfd);
        if (op_ret)
                gf_log (this->name, GF_LOG_WARNING,
                        "failed to set the fd context path=%s fd=%p",
                        loc->path, fd);

        op_ret = 0;

out:
        if (op_ret == -1) {
                if (dir) {
                        closedir (dir);
                        dir = NULL;
                }
                if (pfd) {
                        if (pfd->path)
                                GF_FREE (pfd->path);
                        GF_FREE (pfd);
                        pfd = NULL;
                }
        }

        SET_TO_OLD_FS_ID ();
        STACK_UNWIND_STRICT (opendir, frame, op_ret, op_errno, fd);
        return 0;
}
