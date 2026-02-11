subdir_readlink(const char *path, char *buf, size_t size)
{
	struct subdir *d = subdir_get();
	char *newpath;
	int err = subdir_addpath(d, path, &newpath);
	if (!err) {
		err = fuse_fs_readlink(d->next, newpath, buf, size);
		if (!err && d->rellinks)
			transform_symlink(d, newpath, buf, size);
		free(newpath);
	}
	return err;
}
