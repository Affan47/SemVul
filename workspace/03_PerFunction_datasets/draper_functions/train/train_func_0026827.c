fuse_buf_splice(const struct fuse_buf *dst, size_t dst_off,
			       const struct fuse_buf *src, size_t src_off,
			       size_t len, enum fuse_buf_copy_flags flags)
{
	int splice_flags = 0;
	off_t *srcpos = NULL;
	off_t *dstpos = NULL;
	off_t srcpos_val;
	off_t dstpos_val;
	ssize_t res;
	size_t copied = 0;

	if (flags & FUSE_BUF_SPLICE_MOVE)
		splice_flags |= SPLICE_F_MOVE;
	if (flags & FUSE_BUF_SPLICE_NONBLOCK)
		splice_flags |= SPLICE_F_NONBLOCK;

	if (src->flags & FUSE_BUF_FD_SEEK) {
		srcpos_val = src->pos + src_off;
		srcpos = &srcpos_val;
	}
	if (dst->flags & FUSE_BUF_FD_SEEK) {
		dstpos_val = dst->pos + dst_off;
		dstpos = &dstpos_val;
	}

	while (len) {
		res = splice(src->fd, srcpos, dst->fd, dstpos, len,
			     splice_flags);
		if (res == -1) {
			if (copied)
				break;

			if (errno != EINVAL || (flags & FUSE_BUF_FORCE_SPLICE))
				return -errno;


			return fuse_buf_fd_to_fd(dst, dst_off, src, src_off,
						 len);
		}
		if (res == 0)
			break;

		copied += res;
		if (!(src->flags & FUSE_BUF_FD_RETRY) &&
		    !(dst->flags & FUSE_BUF_FD_RETRY)) {
			break;
		}

		len -= res;
	}

	return copied;
}
