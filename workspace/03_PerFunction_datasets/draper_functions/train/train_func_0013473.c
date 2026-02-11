common_listxattr(struct fuse *f, fuse_req_t req, fuse_ino_t ino,
			    char *list, size_t size)
{
	char *path;
	int err;

	err = get_path(f, ino, &path);
	if (!err) {
		struct fuse_intr_data d;
		fuse_prepare_interrupt(f, req, &d);
		err = fuse_fs_listxattr(f->fs, path, list, size);
		fuse_finish_interrupt(f, req, &d);
		free_path(f, ino, path);
	}
	return err;
}
