glfs_pwritev_async (struct glfs_fd *glfd, const struct iovec *iovec, int count,
		    off_t offset, int flags, glfs_io_cbk fn, void *data)
{
	struct glfs_io *gio = NULL;
	int             ret = 0;

	gio = GF_CALLOC (1, sizeof (*gio), glfs_mt_glfs_io_t);
	if (!gio) {
		errno = ENOMEM;
		return -1;
	}

	gio->iov = iov_dup (iovec, count);
	if (!gio->iov) {
		GF_FREE (gio);
		errno = ENOMEM;
		return -1;
	}

	gio->op     = GF_FOP_WRITE;
	gio->glfd   = glfd;
	gio->count  = count;
	gio->offset = offset;
	gio->flags  = flags;
	gio->fn     = fn;
	gio->data   = data;

	ret = synctask_new (glfs_from_glfd (glfd)->ctx->env,
			    glfs_io_async_task, glfs_io_async_cbk,
			    NULL, gio);

	if (ret) {
		GF_FREE (gio->iov);
		GF_FREE (gio);
	}

	return ret;
}
