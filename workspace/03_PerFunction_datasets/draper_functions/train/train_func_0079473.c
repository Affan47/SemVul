fuse_lib_getattr(fuse_req_t req, fuse_ino_t ino,
			     struct fuse_file_info *fi)
{
	struct fuse *f = req_fuse_prepare(req);
	struct stat buf;
	char *path;
	int err;

	memset(&buf, 0, sizeof(buf));

	if (fi != NULL && f->fs->op.fgetattr)
		err = get_path_nullok(f, ino, &path);
	else
		err = get_path(f, ino, &path);
	if (!err) {
		struct fuse_intr_data d;
		fuse_prepare_interrupt(f, req, &d);
		if (fi)
			err = fuse_fs_fgetattr(f->fs, path, &buf, fi);
		else
			err = fuse_fs_getattr(f->fs, path, &buf);
		fuse_finish_interrupt(f, req, &d);
		free_path(f, ino, path);
	}
	if (!err) {
		struct node *node;

		pthread_mutex_lock(&f->lock);
		node = get_node(f, ino);
		if (node->is_hidden && buf.st_nlink > 0)
			buf.st_nlink--;
		if (f->conf.auto_cache)
			update_stat(node, &buf);
		pthread_mutex_unlock(&f->lock);
		set_stat(f, ino, &buf);
		fuse_reply_attr(req, &buf, f->conf.attr_timeout);
	} else
		reply_err(req, err);
}
