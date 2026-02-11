posix_fsync (call_frame_t *frame, xlator_t *this,
             fd_t *fd, int32_t datasync)
{
        int32_t           op_ret   = -1;
        int32_t           op_errno = 0;
        int               _fd      = -1;
        struct posix_fd * pfd      = NULL;
        int               ret      = -1;
        uint64_t          tmp_pfd  = 0;
        struct iatt       preop = {0,};
        struct iatt       postop = {0,};

        DECLARE_OLD_FS_ID_VAR;

        VALIDATE_OR_GOTO (frame, out);
        VALIDATE_OR_GOTO (this, out);
        VALIDATE_OR_GOTO (fd, out);

        SET_FS_ID (frame->root->uid, frame->root->gid);

#ifdef GF_DARWIN_HOST_OS

        op_ret = 0;
        goto out;
#endif

        ret = fd_ctx_get (fd, this, &tmp_pfd);
        if (ret < 0) {
                op_errno = -ret;
                gf_log (this->name, GF_LOG_WARNING,
                        "pfd not found in fd's ctx");
                goto out;
        }
        pfd = (struct posix_fd *)(long)tmp_pfd;

        _fd = pfd->fd;

        op_ret = posix_fstat_with_gfid (this, _fd, &preop);
        if (op_ret == -1) {
                op_errno = errno;
                gf_log (this->name, GF_LOG_WARNING,
                        "pre-operation fstat failed on fd=%p: %s", fd,
                        strerror (op_errno));
                goto out;
        }

        if (datasync) {
                ;
#ifdef HAVE_FDATASYNC
                op_ret = fdatasync (_fd);
                if (op_ret == -1) {
                        gf_log (this->name, GF_LOG_ERROR,
                                "fdatasync on fd=%p failed: %s",
                                fd, strerror (errno));
                }
#endif
        } else {
                op_ret = fsync (_fd);
                if (op_ret == -1) {
                        op_errno = errno;
                        gf_log (this->name, GF_LOG_ERROR,
                                "fsync on fd=%p failed: %s",
                                fd, strerror (op_errno));
                        goto out;
                }
        }

        op_ret = posix_fstat_with_gfid (this, _fd, &postop);
        if (op_ret == -1) {
                op_errno = errno;
                gf_log (this->name, GF_LOG_WARNING,
                        "post-operation fstat failed on fd=%p: %s", fd,
                        strerror (op_errno));
                goto out;
        }

        op_ret = 0;

out:
        SET_TO_OLD_FS_ID ();

        STACK_UNWIND_STRICT (fsync, frame, op_ret, op_errno, &preop, &postop);

        return 0;
}
