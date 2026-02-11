fuse_send_data_iov_fallback(struct fuse_ll *f, struct fuse_chan *ch,
				       struct iovec *iov, int iov_count,
				       struct fuse_bufvec *buf,
				       size_t len)
{
	struct fuse_bufvec mem_buf = FUSE_BUFVEC_INIT(len);
	void *mbuf;
	int res;


	if (buf->count == 1 && buf->idx == 0 && buf->off == 0 &&
	    !(buf->buf[0].flags & FUSE_BUF_IS_FD)) {


		iov[iov_count].iov_base = buf->buf[0].mem;
		iov[iov_count].iov_len = len;
		iov_count++;
		return fuse_send_msg(f, ch, iov, iov_count);
	}

	res = posix_memalign(&mbuf, pagesize, len);
	if (res != 0)
		return res;

	mem_buf.buf[0].mem = mbuf;
	res = fuse_buf_copy(&mem_buf, buf, 0);
	if (res < 0) {
		free(mbuf);
		return -res;
	}
	len = res;

	iov[iov_count].iov_base = mbuf;
	iov[iov_count].iov_len = len;
	iov_count++;
	res = fuse_send_msg(f, ch, iov, iov_count);
	free(mbuf);

	return res;
}
