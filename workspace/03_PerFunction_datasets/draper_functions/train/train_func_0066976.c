posix_fsyncdir (call_frame_t *frame, xlator_t *this,
                fd_t *fd, int datasync)
{
        int32_t           op_ret   = -1;
        int32_t           op_errno = 0;
        int               ret      = -1;
        struct posix_fd  *pfd      = NULL;

        VALIDATE_OR_GOTO (frame, out);
        VALIDATE_OR_GOTO (this, out);
        VALIDATE_OR_GOTO (fd, out);

        ret = posix_fd_ctx_get (fd, this, &pfd);
        if (ret < 0) {
                op_errno = -ret;
                gf_log (this->name, GF_LOG_WARNING,
                        "pfd is NULL, fd=%p", fd);
                goto out;
        }

        op_ret = 0;

out:
        STACK_UNWIND_STRICT (fsyncdir, frame, op_ret, op_errno);

        return 0;
}
