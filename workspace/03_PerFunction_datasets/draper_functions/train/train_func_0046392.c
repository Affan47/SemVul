vmsplice_to_user(struct file *file, const struct iovec __user *uiov,
			     unsigned long nr_segs, unsigned int flags)
{
	struct pipe_inode_info *pipe;
	struct splice_desc sd;
	long ret;
	struct iovec iovstack[UIO_FASTIOV];
	struct iovec *iov = iovstack;
	struct iov_iter iter;

	pipe = get_pipe_info(file);
	if (!pipe)
		return -EBADF;

	ret = import_iovec(READ, uiov, nr_segs,
			   ARRAY_SIZE(iovstack), &iov, &iter);
	if (ret < 0)
		return ret;

	sd.total_len = iov_iter_count(&iter);
	sd.len = 0;
	sd.flags = flags;
	sd.u.data = &iter;
	sd.pos = 0;

	if (sd.total_len) {
		pipe_lock(pipe);
		ret = __splice_from_pipe(pipe, &sd, pipe_to_user);
		pipe_unlock(pipe);
	}

	kfree(iov);
	return ret;
}
