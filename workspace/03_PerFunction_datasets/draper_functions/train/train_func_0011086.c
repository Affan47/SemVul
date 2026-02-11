fuse_ll_receive_buf(struct fuse_session *se, struct fuse_buf *buf,
			       struct fuse_chan **chp)
{
	struct fuse_chan *ch = *chp;
	struct fuse_ll *f = fuse_session_data(se);
	size_t bufsize = buf->size;
	struct fuse_ll_pipe *llp;
	struct fuse_buf tmpbuf;
	int err;
	int res;

	if (f->conn.proto_minor < 14 || !(f->conn.want & FUSE_CAP_SPLICE_READ))
		goto fallback;

	llp = fuse_ll_get_pipe(f);
	if (llp == NULL)
		goto fallback;

	if (llp->size < bufsize) {
		if (llp->can_grow) {
			res = fcntl(llp->pipe[0], F_SETPIPE_SZ, bufsize);
			if (res == -1) {
				llp->can_grow = 0;
				goto fallback;
			}
			llp->size = res;
		}
		if (llp->size < bufsize)
			goto fallback;
	}

	res = splice(fuse_chan_fd(ch), NULL, llp->pipe[1], NULL, bufsize, 0);
	err = errno;

	if (fuse_session_exited(se))
		return 0;

	if (res == -1) {
		if (err == ENODEV) {
			fuse_session_exit(se);
			return 0;
		}
		if (err != EINTR && err != EAGAIN)
			perror("fuse: splice from device");
		return -err;
	}

	if (res < sizeof(struct fuse_in_header)) {
		fprintf(stderr, "short splice from fuse device\n");
		return -EIO;
	}

	tmpbuf = (struct fuse_buf) {
		.size = res,
		.flags = FUSE_BUF_IS_FD,
		.fd = llp->pipe[0],
	};


	if (res < sizeof(struct fuse_in_header) +
	    sizeof(struct fuse_write_in) + pagesize) {
		struct fuse_bufvec src = { .buf[0] = tmpbuf, .count = 1 };
		struct fuse_bufvec dst = { .buf[0] = *buf, .count = 1 };

		res = fuse_buf_copy(&dst, &src, 0);
		if (res < 0) {
			fprintf(stderr, "fuse: copy from pipe: %s\n",
				strerror(-res));
			fuse_ll_clear_pipe(f);
			return res;
		}
		if (res < tmpbuf.size) {
			fprintf(stderr, "fuse: copy from pipe: short read\n");
			fuse_ll_clear_pipe(f);
			return -EIO;
		}
		buf->size = tmpbuf.size;
		return buf->size;
	}

	*buf = tmpbuf;

	return res;

fallback:
	res = fuse_chan_recv(chp, buf->mem, bufsize);
	if (res <= 0)
		return res;

	buf->size = res;

	return res;
}
