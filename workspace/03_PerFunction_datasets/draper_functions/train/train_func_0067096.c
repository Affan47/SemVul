v9fs_dir_readdir(struct file *file, struct dir_context *ctx)
{
	bool over;
	struct p9_wstat st;
	int err = 0;
	struct p9_fid *fid;
	int buflen;
	int reclen = 0;
	struct p9_rdir *rdir;
	struct kvec kvec;

	p9_debug(P9_DEBUG_VFS, "name %pD\n", file);
	fid = file->private_data;

	buflen = fid->clnt->msize - P9_IOHDRSZ;

	rdir = v9fs_alloc_rdir_buf(file, buflen);
	if (!rdir)
		return -ENOMEM;
	kvec.iov_base = rdir->buf;
	kvec.iov_len = buflen;

	while (1) {
		if (rdir->tail == rdir->head) {
			struct iov_iter to;
			int n;
			iov_iter_kvec(&to, READ | ITER_KVEC, &kvec, 1, buflen);
			n = p9_client_read(file->private_data, ctx->pos, &to,
					   &err);
			if (err)
				return err;
			if (n == 0)
				return 0;

			rdir->head = 0;
			rdir->tail = n;
		}
		while (rdir->head < rdir->tail) {
			p9stat_init(&st);
			err = p9stat_read(fid->clnt, rdir->buf + rdir->head,
					  rdir->tail - rdir->head, &st);
			if (err) {
				p9_debug(P9_DEBUG_VFS, "returned %d\n", err);
				p9stat_free(&st);
				return -EIO;
			}
			reclen = st.size+2;

			over = !dir_emit(ctx, st.name, strlen(st.name),
					 v9fs_qid2ino(&st.qid), dt_type(&st));
			p9stat_free(&st);
			if (over)
				return 0;

			rdir->head += reclen;
			ctx->pos += reclen;
		}
	}
}
