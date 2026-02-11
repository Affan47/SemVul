cusexmp_ioctl(fuse_req_t req, int cmd, void *arg,
			  struct fuse_file_info *fi, unsigned flags,
			  const void *in_buf, size_t in_bufsz, size_t out_bufsz)
{
	int is_read = 0;

	(void)fi;

	if (flags & FUSE_IOCTL_COMPAT) {
		fuse_reply_err(req, ENOSYS);
		return;
	}

	switch (cmd) {
	case FIOC_GET_SIZE:
		if (!out_bufsz) {
			struct iovec iov = { arg, sizeof(size_t) };

			fuse_reply_ioctl_retry(req, NULL, 0, &iov, 1);
		} else
			fuse_reply_ioctl(req, 0, &cusexmp_size,
					 sizeof(cusexmp_size));
		break;

	case FIOC_SET_SIZE:
		if (!in_bufsz) {
			struct iovec iov = { arg, sizeof(size_t) };

			fuse_reply_ioctl_retry(req, &iov, 1, NULL, 0);
		} else {
			cusexmp_resize(*(size_t *)in_buf);
			fuse_reply_ioctl(req, 0, NULL, 0);
		}
		break;

	case FIOC_READ:
		is_read = 1;
	case FIOC_WRITE:
		fioc_do_rw(req, arg, in_buf, in_bufsz, out_bufsz, is_read);
		break;

	default:
		fuse_reply_err(req, EINVAL);
	}
}
