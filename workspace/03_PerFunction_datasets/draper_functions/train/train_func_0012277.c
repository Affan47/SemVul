status_invoke_cb(
	void *cbref, git_diff_delta *i2h, git_diff_delta *w2i)
{
	status_user_callback *usercb = cbref;
	const char *path = NULL;
	unsigned int status = 0;

	if (w2i) {
		path = w2i->old_file.path;
		status |= workdir_delta2status(w2i->status);
	}
	if (i2h) {
		path = i2h->old_file.path;
		status |= index_delta2status(i2h->status);
	}

	return usercb->cb(path, status, usercb->cbdata);
}
