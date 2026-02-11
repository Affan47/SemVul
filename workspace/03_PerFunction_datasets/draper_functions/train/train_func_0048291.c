afr_writev (call_frame_t *frame, xlator_t *this, fd_t *fd,
            struct iovec *vector, int32_t count, off_t offset,
            struct iobref *iobref)
{
        afr_private_t * priv  = NULL;
        afr_local_t   * local = NULL;
        int ret = -1;
        int op_ret   = -1;
        int op_errno = 0;

        VALIDATE_OR_GOTO (frame, out);
        VALIDATE_OR_GOTO (this, out);
        VALIDATE_OR_GOTO (this->private, out);

        priv = this->private;

        QUORUM_CHECK(writev,out);

        ALLOC_OR_GOTO (local, afr_local_t, out);

        ret = AFR_LOCAL_INIT (local, priv);
        if (ret < 0) {
                op_errno = -ret;
                goto out;
        }

        frame->local = local;

        local->cont.writev.vector     = iov_dup (vector, count);
        local->cont.writev.count      = count;
        local->cont.writev.offset     = offset;
        local->cont.writev.iobref     = iobref_ref (iobref);

        local->fd                = fd_ref (fd);
        local->fop_call_continue = afr_do_writev;

        ret = afr_open_fd_fix (frame, this, _gf_true);
        if (ret) {
                op_errno = -ret;
                goto out;
        }

        op_ret = 0;
out:
        if (op_ret == -1) {
                AFR_STACK_UNWIND (writev, frame, op_ret, op_errno, NULL, NULL);
        }

        return 0;
}
