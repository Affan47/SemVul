fuse_ll_retrieve_reply(struct fuse_notify_req *nreq,
				   fuse_req_t req, fuse_ino_t ino,
				   const void *inarg,
				   const struct fuse_buf *ibuf)
{
	struct fuse_ll *f = req->f;
	struct fuse_retrieve_req *rreq =
		container_of(nreq, struct fuse_retrieve_req, nreq);
	const struct fuse_notify_retrieve_in *arg = inarg;
	struct fuse_bufvec bufv = {
		.buf[0] = *ibuf,
		.count = 1,
	};

	if (!(bufv.buf[0].flags & FUSE_BUF_IS_FD))
		bufv.buf[0].mem = PARAM(arg);

	bufv.buf[0].size -= sizeof(struct fuse_in_header) +
		sizeof(struct fuse_notify_retrieve_in);

	if (bufv.buf[0].size < arg->size) {
		fprintf(stderr, "fuse: retrieve reply: buffer size too small\n");
		fuse_reply_none(req);
		goto out;
	}
	bufv.buf[0].size = arg->size;

	if (req->f->op.retrieve_reply) {
		req->f->op.retrieve_reply(req, rreq->cookie, ino,
					  arg->offset, &bufv);
	} else {
		fuse_reply_none(req);
	}
out:
	free(rreq);
	if ((ibuf->flags & FUSE_BUF_IS_FD) && bufv.idx < bufv.count)
		fuse_ll_clear_pipe(f);
}
