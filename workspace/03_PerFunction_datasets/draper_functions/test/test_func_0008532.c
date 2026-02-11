fuse_session_receive_buf(struct fuse_session *se, struct fuse_buf *buf,
			     struct fuse_chan **chp)
{
	int res;

	if (se->receive_buf) {
		res = se->receive_buf(se, buf, chp);
	} else {
		res = fuse_chan_recv(chp, buf->mem, buf->size);
		if (res > 0)
			buf->size = res;
	}

	return res;
}
