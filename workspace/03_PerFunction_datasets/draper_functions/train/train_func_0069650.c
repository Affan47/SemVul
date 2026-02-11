error_gen_writev (call_frame_t *frame, xlator_t *this, fd_t *fd,
		  struct iovec *vector, int32_t count,
		  off_t off, uint32_t flags, struct iobref *iobref, dict_t *xdata)
{
	int              op_errno = 0;
        eg_t            *egp = NULL;
        int              enable = 1;

        egp = this->private;
        enable = egp->enable[GF_FOP_WRITE];

        if (enable)
                op_errno = error_gen (this, GF_FOP_WRITE);

	if (op_errno == GF_ERROR_SHORT_WRITE) {
		struct iovec *shortvec;


		shortvec = iov_dup(vector, 1);
		shortvec->iov_len /= 2;

		STACK_WIND(frame, error_gen_writev_cbk, FIRST_CHILD(this),
			   FIRST_CHILD(this)->fops->writev, fd, shortvec, count,
			   off, flags, iobref, xdata);
		GF_FREE(shortvec);
		return 0;
	} else if (op_errno) {
		GF_ERROR(this, "unwind(-1, %s)", strerror (op_errno));
		STACK_UNWIND_STRICT (writev, frame, -1, op_errno, NULL, NULL, xdata);
        	return 0;
	}

	STACK_WIND (frame, error_gen_writev_cbk,
		    FIRST_CHILD(this),
		    FIRST_CHILD(this)->fops->writev,
		    fd, vector, count, off, flags, iobref, xdata);
        return 0;
}
