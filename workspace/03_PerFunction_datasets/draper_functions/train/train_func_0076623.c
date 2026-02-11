wb_writev (call_frame_t *frame, xlator_t *this, fd_t *fd, struct iovec *vector,
           int32_t count, off_t offset, uint32_t flags, struct iobref *iobref,
           dict_t *xdata)
{
        wb_inode_t   *wb_inode      = NULL;
	wb_conf_t    *conf          = NULL;
        gf_boolean_t  wb_disabled   = 0;
        call_stub_t  *stub          = NULL;
        int           ret           = -1;
        int32_t       op_errno      = EINVAL;
	int           o_direct      = O_DIRECT;

	conf = this->private;

        if (wb_fd_err (fd, this, &op_errno)) {
                goto unwind;
        }

        wb_inode = wb_inode_create (this, fd->inode);
	if (!wb_inode) {
		op_errno = ENOMEM;
		goto unwind;
	}

	if (!conf->strict_O_DIRECT)
		o_direct = 0;

	if (fd->flags & (O_SYNC|O_DSYNC|o_direct))
		wb_disabled = 1;

	if (flags & (O_SYNC|O_DSYNC|o_direct))
		wb_disabled = 1;

	if (wb_disabled)
		stub = fop_writev_stub (frame, wb_writev_helper, fd, vector,
					count, offset, flags, iobref, xdata);
	else
		stub = fop_writev_stub (frame, NULL, fd, vector, count, offset,
					flags, iobref, xdata);
        if (!stub) {
                op_errno = ENOMEM;
                goto unwind;
        }

	if (wb_disabled)
		ret = wb_enqueue (wb_inode, stub);
	else
		ret = wb_enqueue_tempted (wb_inode, stub);

	if (!ret) {
		op_errno = ENOMEM;
		goto unwind;
	}

        wb_process_queue (wb_inode);

        return 0;

unwind:
        STACK_UNWIND_STRICT (writev, frame, -1, op_errno, NULL, NULL, NULL);

        if (stub)
                call_stub_destroy (stub);

        return 0;
}
