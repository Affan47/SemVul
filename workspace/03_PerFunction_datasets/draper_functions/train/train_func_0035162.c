fuse_lib_create(fuse_req_t req, fuse_ino_t parent,
			    const char *name, mode_t mode,
			    struct fuse_file_info *fi)
{
	struct fuse *f = req_fuse_prepare(req);
	struct fuse_intr_data d;
	struct fuse_entry_param e;
	char *path;
	int err;

	err = get_path_name(f, parent, name, &path);
	if (!err) {
		fuse_prepare_interrupt(f, req, &d);
		err = fuse_fs_create(f->fs, path, mode, fi);
		if (!err) {
			err = lookup_path(f, parent, name, path, &e, fi);
			if (err)
				fuse_fs_release(f->fs, path, fi);
			else if (!S_ISREG(e.attr.st_mode)) {
				err = -EIO;
				fuse_fs_release(f->fs, path, fi);
				forget_node(f, e.ino, 1);
			} else {
				if (f->conf.direct_io)
					fi->direct_io = 1;
				if (f->conf.kernel_cache)
					fi->keep_cache = 1;

			}
		}
		fuse_finish_interrupt(f, req, &d);
	}
	if (!err) {
		pthread_mutex_lock(&f->lock);
		get_node(f, e.ino)->open_count++;
		pthread_mutex_unlock(&f->lock);
		if (fuse_reply_create(req, &e, fi) == -ENOENT) {


			fuse_do_release(f, e.ino, path, fi);
			forget_node(f, e.ino, 1);
		}
	} else {
		reply_err(req, err);
	}

	free_path(f, parent, path);
}
